package ru.ifmo.rain.farkhiev.arrayset;

import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class ArraySet<E> extends AbstractSet<E> implements SortedSet<E> {
    private final List<E> array;
    private final Comparator<? super E> comparator;

    public ArraySet() {
        this.array = Collections.emptyList();
        this.comparator = null;
    }

    public ArraySet(Collection<? extends E> array) {
        this(array, null);
    }

    public ArraySet(Collection<? extends E> array, Comparator<? super E> comparator) {
        Set<E> treeSetWrapper = new TreeSet<E>(comparator);
        treeSetWrapper.addAll(array);
        this.array = new ArrayList<>(treeSetWrapper);
        this.comparator = comparator;
    }

    public ArraySet(Comparator<? super E> comparator) {
        this(Collections.emptyList(), comparator);
    }

    public ArraySet(List<E> array, Comparator<? super E> comparator) {
        this.array = array;
        this.comparator = comparator;
    }

    private int processNegativeIndex(int index) {
        return Math.abs(index) - 1;
    }

    private int findIndex(E element) {
        var index = Collections.binarySearch(array, Objects.requireNonNull(element), comparator);
        if (index < 0) index = processNegativeIndex(index);
        return index;
    }

    private SortedSet<E> subSet(E fromElement, E toElement, boolean checker) {
        int fromIndex = findIndex(fromElement);
        int toIndex = findIndex(toElement);
        if(checker)toIndex++;
        return new ArraySet<>(array.subList(fromIndex, toIndex), comparator);
    }

    @Override
    public Iterator<E> iterator() {
        return Collections.unmodifiableList(array).iterator();
    }

    @Override
    public int size() {
        return array.size();
    }

    @Override
    public Comparator<? super E> comparator() {
        return comparator;
    }

    @Override
    public SortedSet<E> subSet(E fromElement, E toElement) {
        if(comparator.compare(fromElement, toElement) > 0){
            throw new IllegalArgumentException();
        }
        return subSet(fromElement, toElement, false);
    }

    @Override
    public SortedSet<E> headSet(E to) {
        return isEmpty() ? new ArraySet<>(Collections.emptyList(), comparator) : subSet(first(), to, false);
    }

    @Override
    public SortedSet<E> tailSet(E from) {
        return isEmpty() ? new ArraySet<>(Collections.emptyList(), comparator) : subSet(from, last(), true);
    }

    @Override
    public E first() {
        if (isEmpty()) throw new NoSuchElementException();
        return array.get(0);
    }

    @Override
    public E last() {
        if (isEmpty()) throw new NoSuchElementException();
        return array.get(size() - 1);
    }

    @Override
    public boolean isEmpty() {
        return array.isEmpty();
    }

    @SuppressWarnings("unchecked")
    @Override
    public boolean contains(Object o) {
        return Collections.binarySearch(array, (E) Objects.requireNonNull(o), comparator) >= 0;
    }

}
