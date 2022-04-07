package il.co.ilrd.hashMap;

import java.util.*;


public class HashMap<K,V> implements Map<K,V> {
    private List<List<Entry<K,V>>> Hashmap;
    private int version;
    // List-bucket-pair. list of 16 buckets, in each bucket there is a linked list. its nodes are the pairs of key & value


    @Override
    public int size() {
        int occupied = 0;

        for(List<Entry<K, V>> rooms: Hashmap)
            occupied += rooms.size();
        return occupied;
    }

    public HashMap(){
        this(16);
    }

    public HashMap(int capacity){
        Hashmap = new ArrayList<>(capacity);
      for(int i = 0; i < capacity ; ++i){
          Hashmap.add(new LinkedList<>());
      }

    }
    @Override
    public void clear() {
        Hashmap.clear();
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
        int hash =  Math.floorMod(key.hashCode(),Hashmap.size());

        return Hashmap.contains(hash);
    }

    @Override
    public boolean containsValue(Object value) {
    for (List<Entry<K, V>> entry : Hashmap) {
            if (entry.equals(value)){
                return true;
            }
        }
        return false;
    }

    @Override
    public V get(Object key) {
        List<Entry<K, V>> floor = Hashmap.get(Math.floorMod(key.hashCode(), Hashmap.size()));
        for(Entry<K, V> room : floor){
            if(room.getKey().equals(key)){
                return room.getValue();
            }
        }

        return null;
    }
    /* create pair.of (key,value);
        hash the key, then % on 16, to get the according bucket.
        in the bucket check if the value isnt already there. if not, store the new pair
          */
    @Override
    public V put(K key, V value) {

        Pair<K,V> newPair =  Pair.of(key,value);
        int hash =  Math.floorMod(key.hashCode(), Hashmap.size());
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

        int hash = Math.floorMod(key.hashCode(), Hashmap.size());
        List<Entry<K, V>> floor = Hashmap.get(Math.floorMod(key.hashCode(), Hashmap.size()));
        V dataToRemove = null;
        for (Entry<K, V> data : floor) {
            if (data.getKey().equals(key)) {
                dataToRemove = data.getValue();
                Hashmap.get(hash).remove(Hashmap.get(hash).indexOf(data));
                ++version;
                return dataToRemove;
            }

        }
        return dataToRemove;

    }

    @Override
    public void putAll(Map<? extends K, ? extends V> map) {
        //enhanced loop in entry set
        for (Map.Entry<? extends K, ? extends V> set : map.entrySet()) this.put(set.getKey(), set.getValue());
    }

    @Override
    public Collection<V> values() {
        return new valuesPairs();
    }

    private class valuesPairs extends AbstractCollection<V> {

        @Override
        public Iterator<V> iterator() {
            return (Iterator<V>) new valuesPairsIterator();
        }

        @Override
        public int size() {
            return Hashmap.size();
        }

        private class valuesPairsIterator implements Iterator<Entry<K, V>> {
            private Set<Entry<K, V>> entry = HashMap.this.entrySet();
            private Iterator<Entry<K, V>> iter = entry.iterator();

            @Override
            public boolean hasNext() {
                return iter.hasNext();
            }

            @Override
            public Entry<K, V> next() {
               return iter.next();

            }
        }
    }


    @Override
    public Set<K> keySet() {
        return new setOfKeys();
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
            private Set<Entry<K, V>> set = HashMap.this.entrySet();
            private Iterator<Entry<K, V>> iter = set.iterator();


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

        return new SetOfPairs();
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
        //fail-fast iterator
            private ListIterator<List<Entry<K,V>>> bucket;
            private Iterator<Entry<K,V>> innerListLocation;
            private final int versionNumber = version;

            private setOfPairsIterator(){
                bucket = Hashmap.listIterator();
                innerListLocation = bucket.next().iterator();
            }

            @Override
            public boolean hasNext() {

                ListIterator<List<Entry<K, V>>> roomRunner = bucket;

                while (roomRunner.hasNext()) {
                   if (!roomRunner.next().isEmpty()){
                       roomRunner.previous();
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
