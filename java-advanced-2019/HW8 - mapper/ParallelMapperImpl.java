package ru.ifmo.rain.farkhiev.mapper;

import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.*;
import java.util.function.Function;

public class ParallelMapperImpl implements ParallelMapper {
    private final ArrayList<Thread> listOfThreads;
    private final Queue<Task> tasks;

    public ParallelMapperImpl(int threads) {
        if (threads <= 0) {
            throw new IllegalArgumentException("Number of threads must be natural");
        }
        tasks = new ArrayDeque<>();
        listOfThreads = new ArrayList<>();
        for (int i = 0; i < threads; i++) {
            Thread thread = new Thread(() -> {
                try {
                    while (!Thread.interrupted()) {
                        Task task;
                        synchronized (tasks) {
                            while (tasks.isEmpty()) {
                                tasks.wait();
                            }
                            task = tasks.poll();
                            tasks.notifyAll();
                        }
                        task.task.run();
                        synchronized (task.counter) {
                            task.counter.add();
                            if (task.counter.check()) {
                                task.counter.notify();
                            }
                        }
                    }
                } catch (InterruptedException ignored) {
                } finally {
                    Thread.currentThread().interrupt();
                }
            });
            listOfThreads.add(thread);
            thread.start();
        }
    }

    /**
     * Class for counter, that counts number of done tasks
     * and check if doing of this task completed.
     */
    private class Counter {
        private int cnt;
        private int needSize;

        Counter(int needSize) {
            this.needSize = needSize;
        }

        void add() {
            cnt++;
        }

        boolean check() {
            return cnt >= needSize;
        }
    }

    private class Task {
        Runnable task;
        final Counter counter;

        Task(Runnable task, Counter counter) {
            this.task = task;
            this.counter = counter;
        }
    }

    @Override
    public <T, R> List<R> map(Function<? super T, ? extends R> f, List<? extends T> args) throws InterruptedException {
        final Counter cnt = new Counter(args.size());
        List<R> res = new ArrayList<R>(Collections.nCopies(args.size(), null));
        for (int i = 0; i < args.size(); i++) {
            final int finalCurElemInd = i;
            synchronized (tasks) {
                tasks.add(new Task(() -> res.set(finalCurElemInd, f.apply(args.get(finalCurElemInd))), cnt));
                tasks.notify();
            }
        }
        synchronized (cnt) {
            while (!cnt.check()) {
                cnt.wait();
            }
        }
        return res;
    }

    @Override
    public void close() {
        for (Thread thread : listOfThreads) {
            thread.interrupt();
        }
        for (Thread thread : listOfThreads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
