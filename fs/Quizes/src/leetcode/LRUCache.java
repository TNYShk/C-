package leetcode;

import org.junit.Test;
import org.testng.Assert;

import java.util.*;

public class LRUCache {
    private final int cap;
   // private Deque<Integer> keyQ;
    private LinkedHashMap<Integer,Integer> lru;

    public LRUCache(int capacity) {
        if(capacity <= 0){
            cap = 16;
        }else{
            cap = capacity;
        }
        lru = new LinkedHashMap<>(cap);

    }

    public int get(int key) {
        if(!lru.containsKey(key))
            return -1;
        Integer val =  lru.get(key);

       lru.remove(key);
       lru.put(key,val);

       return val;

    }

    public void put(int key, int value) {
        if(lru.containsKey(key)){
            lru.remove(key);
        }
        lru.put(key,value);

        if(lru.size() > cap) {
            int leastUsedKey = lru.keySet().iterator().next();
            lru.remove(leastUsedKey);
        }
    }

    public void printMap(){
        System.out.print(lru.keySet());
        System.out.println();
        System.out.print(lru.values());
        System.out.println();
    }



    public static void main(String[] args){
        LRUCache test = new LRUCache(2);
        Assert.assertEquals(-1, test.get(2));
        test.put(2, 6);
        test.printMap();
        Assert.assertEquals(-1, test.get(1));
        test.put(1, 5);
        test.put(1, 2);

        Assert.assertEquals(test.get(1),2);
        test.printMap();

        Assert.assertEquals( test.get(2),6);

    }
  /*  @Test
    public void Uno() {
    LRUCache test = new LRUCache(2);
    test.put(1, 1);
    test.put(2, 2);
    Assert.assertEquals(1, test.get(1));
    test.put(3, 3);
    Assert.assertEquals(-1, test.get(2));
    test.put(4, 4);
    Assert.assertEquals(-1, test.get(1));
    Assert.assertEquals(3, test.get(3));
    Assert.assertEquals(4, test.get(4));
    test.printMap();
    test.printKeyQ();
    }*/
}



