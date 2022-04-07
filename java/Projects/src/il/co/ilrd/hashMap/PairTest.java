package il.co.ilrd.hashMap;

import java.util.*;

import com.sun.media.sound.SoftMixingSourceDataLine;
import org.junit.jupiter.api.Test;
import org.junit.platform.engine.support.descriptor.FileSystemSource;

import static org.junit.jupiter.api.Assertions.*;

public class PairTest {

    @Test
    void testInts(){
        HashSet<Integer> why = new HashSet<>();
        for (int i = 1; i < 5; i++) {
            why.add(i*2);
        }
        Pair<Integer,Integer> pp1 = Pair.of(why.iterator().next(),19);
        Pair<Integer,Integer> pp2 = Pair.of(why.iterator().next(),3);
        Pair<Double,Integer> pp3 = Pair.of(2.0,3);
        Pair<Integer,Integer> pp4 = Pair.of(2,3);
        Pair<Integer,Integer> pp5 = Pair.swap(pp4);
        assertNotEquals(pp1, pp2);
        assertFalse(pp2.equals(pp3));
        assertFalse(pp4.hashCode() == pp3.hashCode());
        assertTrue(Pair.swap(pp5).equals(pp4));

    }
    @Test
    void TestArry(){
        Double[] darry = {1.2,3.2,-5.1,4.4, 0.0, -99.9};
        Pair<Double, Double> pd3 = Pair.minMax(darry);
        assertTrue(Pair.of(-99.9,4.4).equals(pd3));
    }

    @Test
    void TestString(){
        String[] strArry = {"zzzzz","two","aaaa", "four", "three","zzz","one"};
        String shay = "banana";
        System.out.println(shay.hashCode());
        Pair<String, String> s1 = Pair.minMax(strArry,String::compareTo);
        System.out.println(s1.hashCode());
        System.out.println(s1);
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
        assertEquals(myMap.size(), 0);
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
        myMap.put("diennnnnn",2);
        myMap.put("hell",1);
        myMap.put("targil",1);
        for(Map.Entry v: myMap.entrySet()){
            System.out.println(v);
        }
        /*assertEquals(true, myMap.containsValue(2222));*/
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

        System.out.println("Danila");
        assertEquals(true, myMap.containsValue(5666));
        assertEquals(true, myMap.containsKey(47));
        assertEquals(false, myMap.containsKey(55));

    }
    @Test
    void keySetTest(){
        HashMap<String, Integer> myMap = new HashMap<>();
        myMap.put("why",1);
        myMap.put("are",2222);
        myMap.put("you",333);
        myMap.put("so",44);
        myMap.put("angry",54);
        System.out.println(myMap.values());
        System.out.println(myMap.entrySet());
        System.out.println(myMap.keySet());
        myMap.remove("angry");
        myMap.remove("so");
        assertEquals(3,myMap.size());
        for(String v: myMap.keySet()) {
            System.out.print(v + " ");
        }
        System.out.println();
        for(Integer v: myMap.values()) {
            System.out.print(v+ " ");
        }


    }
}