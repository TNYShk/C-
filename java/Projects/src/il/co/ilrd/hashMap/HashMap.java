package il.co.ilrd.hashMap;

import java.util.*;


public class HashMap<K,V> implements Map<K,V> {
    private final List<List<Entry<K,V>>> Hashmap;
    private int version;
    private Set<Entry<K,V>> SetOfEntries = null;
    private Set<K> Setofkeys = null;
    private Collection<V> valuesCollection = null;
    private final int capacity;


    public HashMap(){
        this(16);
    }

    public HashMap(int capacity){
        this.capacity = capacity;
        Hashmap = new ArrayList<>(capacity);

        for(int i = 0; i < capacity ; ++i){
          Hashmap.add(new LinkedList<>());
        }
    }

    @Override
    public int size() {
        int occupied = 0;

        for(List<Entry<K, V>> rooms: Hashmap)
            occupied += rooms.size();
        return occupied;
    }

    @Override
    public void clear() {
        Hashmap.clear();
        for(int i = 0; i < capacity ; ++i){
            Hashmap.add(new LinkedList<>());
        }
        ++version;
    }

    @Override
    public boolean isEmpty() {
        for(List<Entry<K, V>> rooms: Hashmap){
               if(!rooms.isEmpty()){
                   return false;
               }
            }
        return true;
    }

    @Override
    public boolean containsKey(Object key) {
        List<Entry<K, V>> floor = Hashmap.get(Math.floorMod(key.hashCode(), capacity));

        for(Entry<K, V> room : floor){
            if(room.getKey().equals(key)){
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean containsValue(Object value) {
        for (Map.Entry entry : this.entrySet()) {
                if (entry.getValue().equals(value)){
                    return true;
                }
            }
            return false;
    }

    @Override
    public V get(Object key) {
        List<Entry<K, V>> floor = Hashmap.get(Math.floorMod(key.hashCode(), capacity));
        for(Entry<K, V> room : floor){
            if(room.getKey().equals(key)){
                return room.getValue();
            }
        }

        return null;
    }

    @Override
    public V put(K key, V value) {
        Pair<K,V> newPair =  Pair.of(key,value);
        int hash =  Math.floorMod(key.hashCode(), capacity);

        for(Entry<K,V> match: Hashmap.get(hash)) {
            if (match.getKey().equals(key)) {
                ++version;
                return match.setValue(value);
            }
        }
        ++version;
        Hashmap.get(hash).add(newPair);
        return null;
    }

    @Override
    public V remove(Object key) {
        int hash = Math.floorMod(key.hashCode(),capacity);
        List<Entry<K, V>> floor = Hashmap.get(Math.floorMod(key.hashCode(), capacity));

        for (Entry<K, V> data : floor) {
            if (data.getKey().equals(key)) {
                V dataToRemove = data.getValue();
                Hashmap.get(hash).remove(data);
                ++version;
                return dataToRemove;
            }
        }
        return null;
    }

    @Override
    public void putAll(Map<? extends K, ? extends V> map) {

        for (Map.Entry<? extends K, ? extends V> set : map.entrySet()) this.put(set.getKey(), set.getValue());
    }

    @Override
    public Collection<V> values() {
        if(null == valuesCollection){
            valuesCollection = new valuesPairs();
        }
        return valuesCollection;
    }

    private class valuesPairs extends AbstractCollection<V> {

        @Override
        public Iterator<V> iterator() {
            return new valuesPairsIterator();
        }

        @Override
        public int size() {
            return Hashmap.size();
        }

        private class valuesPairsIterator implements Iterator<V> {
            private Iterator<Entry<K, V>> iter = HashMap.this.entrySet().iterator();

            @Override
            public boolean hasNext() {
                return iter.hasNext();
            }

            @Override
            public V next() {
               return iter.next().getValue();

            }
        }
    }

    @Override
    public Set<K> keySet() {
        if(null == Setofkeys){
            Setofkeys = new setOfKeys();
        }
        return Setofkeys;
    }

    private class setOfKeys extends AbstractSet<K>{

        @Override
        public Iterator<K> iterator() {
            return new setOfKeysIterator();
        }

        @Override
        public int size() {
           return Hashmap.size();
        }

        private class setOfKeysIterator implements Iterator<K>{
            private Iterator<Entry<K, V>> iter = HashMap.this.entrySet().iterator();


            @Override
            public boolean hasNext() {
               return iter.hasNext();
            }

            @Override
            public K next() {
                return iter.next().getKey();
            }
        }
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        if(null == SetOfEntries){
            SetOfEntries = new SetOfPairs();
        }
        return SetOfEntries;
    }

    private class SetOfPairs extends AbstractSet<Entry<K,V>>{

        @Override
        public Iterator<Entry<K,V>> iterator() {
            return new setOfPairsIterator();
        }

        @Override
        public int size() {
            return Hashmap.size();
        }

        private class setOfPairsIterator implements Iterator<Entry<K,V>>{
            private ListIterator<List<Entry<K,V>>> bucket;
            private Iterator<Entry<K,V>> innerListLocation;
            private final int versionNumber = version;

            private setOfPairsIterator(){
                bucket = Hashmap.listIterator();
                innerListLocation = bucket.next().iterator();
            }

            @Override
            public boolean hasNext() {

                while (bucket.hasNext()) {
                   if (!bucket.next().isEmpty()){
                       bucket.previous();
                       return true;
                   }
                }
                return false;
            }

            @Override
            public Entry<K, V> next() {
                if(version != versionNumber){
                        throw new ConcurrentModificationException();
                }
                if(innerListLocation.hasNext()){
                    return innerListLocation.next();
                }

                while(bucket.hasNext()){
                    List<Entry<K,V>> bucketIter = bucket.next();
                    if(!bucketIter.isEmpty()){
                        innerListLocation = bucketIter.iterator();
                        return  innerListLocation.next();
                    }
                }
            return null;
            }
        }
    }
}
