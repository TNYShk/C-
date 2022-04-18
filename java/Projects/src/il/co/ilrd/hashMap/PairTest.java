package il.co.ilrd.hashMap;

import java.util.ConcurrentModificationException;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class PairTest {

    @Test
    void PairtestInts(){
        HashSet<Integer> why = new HashSet<>();
        for (int i = 1; i < 5; i++) {
            why.add(i * 2);
        }
        Pair<Integer,Integer> pp1 = Pair.of(why.iterator().next(),19);
        Pair<Integer,Integer> pp2 = Pair.of(why.iterator().next(),3);
        Pair<Double,Integer> pp3 = Pair.of(2.0,3);
        Pair<Integer,Integer> pp4 = Pair.of(2,3);
        Pair<Integer,Integer> pp5 = Pair.swap(pp4);
        Pair<Integer,Integer> pp6 = Pair.of(null,3);
        System.out.print(pp6);
        assertNotEquals(pp1, pp2);
        assertFalse(pp2.equals(pp3));
        assertFalse(pp4.hashCode() == pp3.hashCode());
        assertTrue(Pair.swap(pp5).equals(pp4));
    }

    @Test
    void PairTestArry(){
        Double[] darry = {1.2,3.2,-5.1,4.4, 0.0, -99.9};
        Pair<Double, Double> pd3 = Pair.minMax(darry);
        assertTrue(Pair.of(-99.9,4.4).equals(pd3));


    }

    @Test
    void PairTestString(){
        String[] strArry = {"zzzzz","two","aaaa", "four", "three","zzz","one"};
        String shay = "banana";
        System.out.println(shay.hashCode());
        Pair<String, String> s1 = Pair.minMax(strArry,String::compareTo);
        Pair<String, String> s2 = Pair.LazyMinMax(strArry, null);
        System.out.println(s1.hashCode());
        System.out.println(s1);
        System.out.println(s2);
        assertTrue(s1.getKey().equals("aaaa"));
        assertTrue(s1.getValue().equals("zzzzz"));
    }

    public static void main (String []args){
        Pair<Integer,Integer> t = Pair.of(2,6);
        System.out.println(t);
    }

    @Test
    void HashTest(){
        HashMap<String, Integer> myMap = new HashMap<>();
        assertTrue(myMap.isEmpty());
      
        myMap.put("die",1);
        myMap.put("antwood",2222);
        myMap.put("south",3);
        myMap.put("africa",4);
        assertEquals(true, myMap.containsValue(2222));

        for(Map.Entry v: myMap.entrySet()){
            System.out.println(v);
        }

        assertEquals(4, myMap.size());
        assertFalse(myMap.isEmpty());
        myMap.remove("die");
        assertEquals(3, myMap.size());
        myMap.clear();
        assertTrue(myMap.isEmpty());
        myMap.put("previous",2);
        myMap.put("was",1);
        myMap.put("here",1);

        for(Map.Entry v: myMap.entrySet()){
            System.out.println(v);
        }
    }

    @Test
    void HashPrintTest(){
        HashMap<Integer, Integer> myMap = new HashMap<>();

        myMap.put(1,2);
        myMap.put(2,3);
        Set<Map.Entry<Integer, Integer>> test = myMap.entrySet();

        myMap.put(4,5);
        myMap.put(47,5666);
        try{
            for(Map.Entry v: test) {
                System.out.println(v);
                myMap.put(444, 5);
            }
            }catch (ConcurrentModificationException e){
                System.err.println(e);
            }

        assertEquals(true, myMap.containsValue(5666));
        assertEquals(true, myMap.containsKey(47));
        assertEquals(false, myMap.containsKey(55));
        assertEquals(5, myMap.size());
        System.out.println("post try catch clause");
    }
    @Test
    void HashkeySetTest(){
        HashMap<String, Integer> myMap = new HashMap<>();
        myMap.put("Beer Sheba",4);
        myMap.put("Hadera",2);
        myMap.put("Bne Brak",5);
        myMap.put("Tel Aviv",2);
        myMap.put("STOP",13);

        System.out.println(myMap.values());
        System.out.println(myMap.entrySet());
        System.out.println(myMap.keySet());
        myMap.remove("STOP");

        assertEquals(4,myMap.size());
        for(String v: myMap.keySet()) {
            System.out.print(v + " ");
        }
        System.out.println();
        for(Integer v: myMap.values()) {
            System.out.print(v+ " ");
        }

    }
    @Test
    void HashPutAllTest(){
        HashMap<String, Integer> myMap = new HashMap<>();
        myMap.put("how",11);
        myMap.put("many",222);
        myMap.put("terror",3333);
        myMap.put("acts?!",44444);
        myMap.put("enough!",555555);
        myMap.put(null,66666);
        myMap.remove(null);
        HashMap<String, Integer> newwerHashMap = new HashMap<>();
        newwerHashMap.putAll(myMap);
        System.out.println(newwerHashMap.keySet());
        System.out.println(newwerHashMap.values());

        assertEquals(myMap.size(), newwerHashMap.size());
    }

    @Test
    void toughTest() {
        HashMap<Integer, Integer> map1 = new HashMap<>();
        for (int i = 0; i < 100; ++i) {
            map1.put(i, i * i);
        }

        assertEquals(map1.size(), 100);
        assertEquals(map1.entrySet().size(), 100);
        assertEquals(map1.keySet().size(), 100);
        assertEquals(map1.values().size(), 100);

      for (int i = 0; i < 100; ++i) {
          assertTrue(map1.entrySet().contains(Pair.of(i, i * i)));
            assertTrue(map1.containsKey(i));
            assertTrue(map1.containsValue(i * i));
        }
    }
}
