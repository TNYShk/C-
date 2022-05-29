package il.co.ilrd.datastructures;

import java.util.ArrayList;
import java.util.Collections;

public class Hasher<K,V> {

    private static class LinkedListNode<K,V>{
        public LinkedListNode<K,V> next;
        public LinkedListNode<K,V> prev;
        public K key;
        public V value;

        public LinkedListNode(K k, V v){
            key = k;
            value = v;
        }
    }

    private ArrayList<LinkedListNode<K,V>> floor;

    public Hasher(int capacity){
        floor = new ArrayList<LinkedListNode<K,V>>();
        floor.ensureCapacity(capacity);
        for(int i= 0; i< capacity; ++i){
            floor.add(null);
        }
    }

    public void put(K key, V value){
        LinkedListNode<K,V> room = getNodeForKey(key);
        if(room != null){
            room.value = value;
            return;
        }
        room = new LinkedListNode<>(key,value);
        int idx = getIndexForKey(key);
        if(floor.get(idx) != null){
            room.next = floor.get(idx);
            room.next.prev = room;
        }
        floor.set(idx,room);
    }

    public void remove(K key){
        LinkedListNode<K,V> room = getNodeForKey(key);
        if(room.prev != null){
            room.prev.next = room.next;
        }else{
            int hashKey = getIndexForKey(key);
            floor.set(hashKey,room.next);
        }
        if(room.next != null)
            room.next.prev = room.prev;
    }

    public V get(K key){
        LinkedListNode<K,V> getter = getNodeForKey(key);
        return getter == null? null: getter.value;
    }

    private LinkedListNode<K,V> getNodeForKey(K key){
        int idx = getIndexForKey(key);
        LinkedListNode<K,V> current = floor.get(idx);
        while(current != null){
            if(current.key == key)
                return current;
            current = current.next;
        }
        return null;
    }

    public int getIndexForKey(K key){
        return Math.abs(key.hashCode() % floor.size());
    }


    public static void main(String []args){
        Hasher<Integer,String> hotel = new Hasher<>(26);
        hotel.put(1,"Tanya");
        hotel.put(2,"Igal");
        hotel.put(1,"Maya");
        hotel.put(2,"Adam");

      System.out.println(hotel.getNodeForKey(1).value);

        System.out.println(hotel.getNodeForKey(2).value);


    }
}
