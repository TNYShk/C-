package il.co.ilrd.quiz_lruc;

import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedList;

public class quizLRUCache<K,V> {
    private final int capacity;
    private static final int MIN_CAP = 16;
    private Deque<K> keyQ;
    private HashMap<K,V> hashMap;


    public quizLRUCache(int capacity){
        if(capacity< MIN_CAP)
            capacity = MIN_CAP;

        hashMap = new HashMap<>(capacity);
        keyQ = new LinkedList<>();
        this.capacity = capacity;
    }
    public quizLRUCache(){
        this(MIN_CAP);
    }

    public void put(K key, V value){
        if(keyQ.size() == capacity){
            K some = keyQ.removeLast();
            hashMap.remove(some);
        }
        else{
            keyQ.remove(key);
            hashMap.remove(key,value);
        }
        keyQ.push(key);
        hashMap.put(key,value);
    }

    public V get(K key){
       V used = hashMap.get(key);
       hashMap.remove(key,used);
       keyQ.remove(key);

      put(key,used);
       return used;
    }

    public void print(){
        //System.out.println(hashMap.keySet());
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
