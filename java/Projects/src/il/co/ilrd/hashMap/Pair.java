package il.co.ilrd.hashMap;


import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
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
       V current = this.value;
        this.value = value;
       return current;
    }

    public K setKey(K key) {
        K current = this.key;
       this.key = key;
        return current;
    }

    @Override
    public int hashCode() {
        final int prime = 101;
        int hash = 11;

        if (null != key) {
            hash = hash * prime + key.hashCode();
        }

        if (null != value) {
            hash = hash * prime + value.hashCode();
        }

        return hash;



    }

    @Override
    public boolean equals(Object other) {
        if(other instanceof Pair){
            return (this.key.equals(((Pair<?, ?>) other).key) && this.value.equals(((Pair<?,?>) other).value));
        }
        return false;
    }


    public static <E extends Comparable<E>> Pair<E, E> minMax(E [] elementsArray){
        List<E> list = Arrays.asList(elementsArray);
        return new Pair<>(Collections.min(list), Collections.max(list));


    }
    public static <E> Pair<E, E> LazyMinMax(E [] elementsArray, Comparator<E> cmpFun){

        List<E> list = Arrays.asList(elementsArray);
        return new Pair<E, E>(Collections.min(list, cmpFun), Collections.max(list, cmpFun));
    }

    //time complex o(1.5)
    public static <E> Pair<E, E> minMax(E [] elementsArray, Comparator<E> cmpFun){

        E min = elementsArray[elementsArray.length - 1];
        E max = elementsArray[elementsArray.length - 1];

        for (int i = 0; i < (elementsArray.length >>1) ; ++i) {
            if (0 > cmpFun.compare(elementsArray[2 * i], elementsArray[(2 * i) + 1])) {
                if (0 > cmpFun.compare(elementsArray[2 * i], min) ) {
                    min = elementsArray[ 2 * i ];
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
        return ("[" + this.getKey()  + " , " + this.getValue() + "]");
    }

}
