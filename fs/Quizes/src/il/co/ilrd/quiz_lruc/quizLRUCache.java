package il.co.ilrd.quiz_lruc;

import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.LinkedList;

public class quizLRUCache<K,V> {
    private final int capacity;
    private static final int MIN_CAP = 16;

    private LinkedHashMap<K,V> hashMap;


    public quizLRUCache(int capacity){
        if(capacity< MIN_CAP)
            capacity = MIN_CAP;
        hashMap = new LinkedHashMap<>(capacity);
        this.capacity = capacity;
    }
    public quizLRUCache(){
        this(MIN_CAP);
    }

    public void put(K key, V value){

        if(hashMap.containsKey(key)){
            hashMap.remove(key);
        }
        hashMap.put(key,value);

        if(hashMap.size() > capacity) {
            K leastUsedKey = hashMap.keySet().iterator().next();
            hashMap.remove(leastUsedKey);
        }
    }

    public V get(K key){
        if(!hashMap.containsKey(key))
            return null;
        V val =  hashMap.get(key);

        hashMap.remove(key);
        hashMap.put(key,val);

        return val;

    }

    public void print(){
        System.out.println(hashMap.keySet());
        System.out.println(hashMap.values());
    }

    public static void main(String [] argc) {
        quizLRUCache<Integer,Integer> cache = new quizLRUCache<>();
        cache.put(1, 10);
        cache.put(2, 20);
        cache.put(3, 30);
        cache.put(4, 40);
        cache.put(5, 50);

        cache.put(3, 300);
        cache.put(0, 0);
        cache.put(6, 60);
        cache.put(7, 18);
        cache.print();
        Integer data = cache.get(4);
        System.out.println(data);
        cache.print();




    }

}
