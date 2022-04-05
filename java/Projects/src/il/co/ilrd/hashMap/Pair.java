package il.co.ilrd.hashMap;


import java.util.*;

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
        return (key.hashCode()^value.hashCode());
    }

    @Override
    public boolean equals(Object other) {
        if(other instanceof Pair){
            return (this.key.equals(((Pair<?, ?>) other).key) && this.value.equals(((Pair<?, ?>) other).value));
        }
        return false;
    }


    public static <E extends Comparable<E>> Pair<E, E> minMax(E [] elementsArray){
        List<E> list = Arrays.asList(elementsArray);

        return new Pair<>(Collections.min(list), Collections.max(list));


    }
    //time complex o(1.5)
    public static <E> Pair<E, E> minMax(E [] elementsArray, Comparator<E> cmpFun){

        E min = elementsArray[0];
        E max = elementsArray[elementsArray.length-1];

        for (int i = 0; i < (elementsArray.length / 2); ++i) {
            if (0 > cmpFun.compare(elementsArray[2 * i], elementsArray[(2 * i) + 1])) {
                if (0 > cmpFun.compare(elementsArray[2 * i], min) ) {
                    min = elementsArray[2 * i];
                }
                if (0 < cmpFun.compare(elementsArray[(2 * i) + 1], max)) {
                    max = elementsArray[(2 * i) + 1];
                }
            }
            else {
                if (0 > cmpFun.compare(elementsArray[(2 * i) + 1], min)) {
                    min = elementsArray[(2 * i) + 1];
                }
                if (0 < cmpFun.compare(elementsArray[2 * i], max)) {
                    max = elementsArray[2 * i];
                }
            }
        }

        return new Pair<>(min, max);
    }

    public static <K, V> Pair<K, V> of(K key, V value) {
        return new Pair<>(key,value);
    }

    public static <K, V> Pair<V, K> swap(Pair<K, V> pair) {
        return new Pair<>(pair.value, pair.key);

    }

    @Override
    public String toString(){
        return (this.getKey()  + " , " + this.getValue());
    }

}
