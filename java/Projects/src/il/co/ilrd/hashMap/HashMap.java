package il.co.ilrd.hashMap;

import java.util.*;


public class HashMap<K,V> implements Map<K,V> {
    private List<List<Entry<K,V>>> HashMap;
    private int version;
    // List-bucket-pair. list of 16 buckets, in each bucket there is a linked list. its nodes are the pairs of key & value


    @Override
    public int size() {
        return 0;
    }

    public HashMap(){
        this(16);
    }

    public HashMap(int capacity){
      HashMap = new ArrayList<List<Entry<K,V>>>(capacity);
      /*for(List: HashMap){*/


    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public boolean containsKey(Object key) {
        return false;
    }

    @Override
    public boolean containsValue(Object value) {
        return false;
    }

    @Override
    public V get(Object o) {
        return null;
    }

    @Override
    public Object put(Object key, Object value) {
       /* create pair.of (key,value);
        hash the key, then % on 16, to get the according bucket. in the bucket check if the value isnt already there. if not, store the new pair
        */
        return null;

    }

    @Override
    public V remove(Object key) {
        return null;
    }

    @Override
    public void putAll(Map<? extends K, ? extends V> map) {
        //enhaced loop in entry set
    }

    @Override
    public void clear() {
    // empties hash
    }

    @Override
    public Collection<V> values() {
        return null;
    }

    private class valuesPairs extends AbstractCollection<V> {

        @Override
        public Iterator<V> iterator() {
            return null;
        }

        @Override
        public int size() {
            return 0;
        }

        private class valuesPairsIterator implements Iterator<Entry<K, V>> {
            @Override
            public boolean hasNext() {
                return false;
            }

            @Override
            public Entry<K, V> next() {
                return null;
            }
        }
    }


    @Override
    public Set keySet() {
        return null;
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
            return null;
        }

        @Override
        public int size() {
            return HashMap.this.size();
        }

        private class setOfPairsIterator implements Iterator<Entry<K,V>>{
        //fail-fast iterator
            private Iterator<List<Entry<K,V>>> bucket;
            private Iterator<Entry<K,V>> innerListLocation;
            private final int versionNumber = version;

            setOfPairsIterator(){

            }
            @Override
            public boolean hasNext() {
                //allow null data so extra checks
                return false;
            }

            @Override
            public Entry<K, V> next() {
                return null;
            }
        }
    }
}
