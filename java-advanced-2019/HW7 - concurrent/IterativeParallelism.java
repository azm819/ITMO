package ru.ifmo.rain.farkhiev.concurrent;

import info.kgeorgiy.java.advanced.concurrent.ScalarIP;
import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.*;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Stream;

public class IterativeParallelism implements ScalarIP {
    private final ParallelMapper mapper;

    /**
     * Finds maximum. Separate for {@link Thread} and finds maximum using these threads
     *
     * @param threads    number or concurrent threads.
     * @param values     values to get maximum of.
     * @param comparator value comparator.
     * @param <T>
     * @return first maximum of list of values
     * @throws InterruptedException {@linkplain InterruptedException} for Error of Interrupting
     */
    @Override
    public <T> T maximum(int threads, List<? extends T> values, Comparator<? super T> comparator) throws InterruptedException {
        return task(threads, values, stream -> stream.max(comparator).orElseThrow(), stream -> stream.max(comparator).orElseThrow());
    }

    /**
     *
     * @param mapper
     */
    public IterativeParallelism(ParallelMapper mapper){
        this.mapper = mapper;
    }

    /**
     *
     */
    public IterativeParallelism(){
        mapper = null;
    }

    /**
     * Finds minimum. Separate for {@link Thread} and finds maximum using these threads.
     *
     * @param threads    number or concurrent threads.
     * @param values     values to get minimum of.
     * @param comparator value comparator.
     * @param <T>
     * @return {@linkplain #maximum(int, List, Comparator) maximum} with reversed {@linkplain Comparator}
     * @throws InterruptedException {@linkplain InterruptedException} for Error of Interrupting
     */
    @Override
    public <T> T minimum(int threads, List<? extends T> values, Comparator<? super T> comparator) throws InterruptedException {
        return maximum(threads, values, Collections.reverseOrder(comparator));
    }

    private <T, R> R task(int threads, List<? extends T> values, Function<Stream<? extends T>, R> function, Function<Stream<R>, R> result) throws InterruptedException {
        if (threads <= 0) {
            throw new IllegalArgumentException("Number of threads must be natural");
        }
        Objects.requireNonNull(values);
        List<Stream<? extends T>> subLists = new ArrayList<>();
        int numberOfThreads = Math.max(1, Math.min(threads, values.size()));
        int size = values.size();
        int eachSize = size / numberOfThreads;
        int restSize = size % numberOfThreads;
        for (int i = 0, l, r = 0; i < numberOfThreads; i++) {
            l = r;
            r = l + eachSize;
            if (restSize > 0) {
                r++;
            }
            restSize--;
            int finalL = l;
            int finalR = r;
            subLists.add(values.subList(finalL, finalR).stream());
        }
        List<R> threadValues;
        if(mapper == null) {
            List<Thread> listOfThreads = new ArrayList<>();
            threadValues = new ArrayList<R>(Collections.nCopies(numberOfThreads, null));
            for (int i = 0; i < numberOfThreads; ++i){
                int finalI = i;
                var thread = new Thread(() -> threadValues.set(finalI, function.apply(subLists.get(finalI))));
                thread.start();
                listOfThreads.add(thread);
            }
            for (var thread : listOfThreads) {
                thread.join();
            }
        } else {
            threadValues = mapper.map(function, subLists);
        }
        return result.apply(threadValues.stream());
    }

    /**
     * Check if all.
     *
     * @param threads   number or concurrent threads.
     * @param values    values to test.
     * @param predicate test predicate.
     * @param <T>       Template
     * @return true if there are all, false in other
     * @throws InterruptedException {@linkplain InterruptedException} for Error of Interrupting
     */
    @Override
    public <T> boolean all(int threads, List<? extends T> values, Predicate<? super T> predicate) throws InterruptedException {
        return task(threads, values, stream -> stream.allMatch(predicate), stream -> stream.allMatch(Boolean::booleanValue));
    }

    /**
     * Check if any.
     *
     * @param threads   number or concurrent threads.
     * @param values    values to test.
     * @param predicate test predicate.
     * @param <T>       Template
     * @return true if there are any, false in other
     * @throws InterruptedException {@linkplain InterruptedException} for Error of Interrupting
     */
    @Override
    public <T> boolean any(int threads, List<? extends T> values, Predicate<? super T> predicate) throws InterruptedException {
        return !all(threads, values, predicate.negate());
    }
}
