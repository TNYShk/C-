package il.co.ilrd.hashMap;

import java.util.*;


public class HashMap<K,V> implements Map<K,V> {
    private List<List<Entry<K,V>>> HashMap;
    private int version;
    // List-bucket-pair. list of 16 buckets, in each bucket there is a linked list. its nodes are the pairs of key & value


    @Override
    public int size() {
        int occupied = 0;

        for(List<Entry<K, V>> rooms: HashMap)
            occupied += rooms.size();
        return occupied;
    }

    public HashMap(){
        this(16);
    }

    public HashMap(int capacity){
      HashMap = new ArrayList<>(capacity);
      for(int i = 0; i < capacity ; ++i){
          HashMap.add(new LinkedList<>());
      }

    }
    @Override
    public void clear() {
      Collections.fill(HashMap, null);
        ++version;
    }

    @Override
    public boolean isEmpty() {
        for(List<Entry<K, V>> rooms: HashMap){
               if(!rooms.isEmpty()){
                   return false;
               }
            }
        return true;
    }

    @Override
    public boolean containsKey(Object key) {
        int hash =  Math.floorMod(key.hashCode(),16);
        return HashMap.contains(hash);
    }

    @Override
    public boolean containsValue(Object value) {
        return HashMap.contains(value);

    }

    @Override
    public V get(Object key) {
        if(containsKey(key)){
            List<Entry<K, V>> floor = HashMap.get(Math.floorMod(key.hashCode(), HashMap.size()));
            for(Entry<K, V> room : floor){
                if(key.equals(room.getKey())){
                    return room.getValue();
                }
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
        int hash =  Math.floorMod(key.hashCode(),16);
        for(Entry<K,V> match: HashMap.get(hash)) {
            if (match.getKey().equals(key)) {
                ++version;
                return match.setValue(value);
            }
        }
        ++version;
        HashMap.get(hash).add(newPair);
        return value;
    }

    @Override
    public V remove(Object key) {
        int hash = Math.floorMod(key.hashCode(),16);
        V dataToRemove = get(hash);
        HashMap.remove(key);

        ++version;
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
            return HashMap.size();
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
           return HashMap.size();
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
                return iterator().next();
            }
        }
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        //Set is ds interface? need inner class for it- collection of unique elements
        //return setofPairs object
        return new SetOfPairs();
    }

    private class SetOfPairs extends AbstractSet<Entry<K,V>>{

        @Override
        public Iterator<Entry<K,V>> iterator() {
            return new setOfPairsIterator();

        }

        @Override
        public int size() {
            return HashMap.size();
        }

        private class setOfPairsIterator implements Iterator<Entry<K,V>>{
        //fail-fast iterator
            private Iterator<List<Entry<K,V>>> bucket;
            private Iterator<Entry<K,V>> innerListLocation;
            private final int versionNumber = version;

            private setOfPairsIterator(){
                bucket = HashMap.listIterator();
                Iterator<List<Entry<K,V>>> runner = bucket;
                innerListLocation = runner.next().listIterator();
            }
            @Override
            public boolean hasNext() {
                List<Entry<K,V>> bucky = null;

                for(Iterator<List<Entry<K,V>>> floor = bucket ; floor.hasNext(); bucky = floor.next()) {
                    if (!bucky.isEmpty()){
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
                for(Iterator<List<Entry<K,V>>> floor = bucket; floor.hasNext();floor.next()) {
                    for (Iterator<Entry<K, V>> room = innerListLocation; room.hasNext(); ) {
                        return (Entry<K, V>) Pair.of(floor, room);
                    }
                }
               return null;
            }
        }
    }
}
