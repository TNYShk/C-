package il.co.ilrd.complex.hashMap;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Set;


public class HashMap<K,V> implements Map<K,V> {
    private List<List<Entry<K,V>>> HashMap;

    private int capacity = 16;

    @Override
    public int size() {
        return 0;
    }
    public HashMap(){}

    public HashMap(int capacity){
        this.capacity = capacity;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public boolean containsKey(Object o) {
        return false;
    }

    @Override
    public boolean containsValue(Object o) {
        return false;
    }

    @Override
    public V get(Object o) {
        return null;
    }

    @Override
    public Object put(Object o, Object o2) {
        return null;
    }

    @Override
    public V remove(Object key) {
        return null;
    }

    @Override
    public void putAll(Map map) {
    }

    @Override
    public void clear() {
    // empties hash
    }

    @Override
    public Collection<V> values() {
        return null;
    }

    @Override
    public Set keySet() {
        return null;
    }
    @Override
    public Set<Entry<K, V>> entrySet() {
        return null;
    }
}
