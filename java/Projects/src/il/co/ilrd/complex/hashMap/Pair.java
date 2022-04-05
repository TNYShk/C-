package il.co.ilrd.complex.hashMap;

import java.util.Comparator;
import java.util.Map;

public class Pair <K, V> implements Map.Entry<K, V> {
    private K key;
    private V value;

    private Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    @Override
    public K getKey() {
       return key;

    }

    @Override
    public V getValue() {
       return value;
    }

    @Override
    public V setValue(V value) {
       this.value = value;
       return value;
    }

    public K setKey(K key) {
       this.key = key;
        return key;
    }

    @Override
    public int hashCode() {
        return key.hashCode()<<31;
    }

    @Override
    public boolean equals(Object other) {
        if(other instanceof Pair){
            return (this.key.equals(((Pair<?, ?>) other).key) && this.value.equals(((Pair<?, ?>) other).value));
        }
        return false;
    }

    //time complex o(1.5)
    public static <E extends Comparable<E>> Pair<E, E> minMax(E [] elementsArray){
        return null;
    }

    public static <E> Pair<E, E> minMax(E [] elementsArray, Comparator<E> comparFunction){
        return null;
    }

    public static <K, V> Pair<K, V> of(K key, V value) {
        return new Pair<>(key,value);

    }

    public static <K, V> Pair<V, K> swap(Pair<K, V> pair) {
        return null;
    }

}
