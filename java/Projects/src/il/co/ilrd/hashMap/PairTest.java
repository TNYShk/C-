package il.co.ilrd.hashMap;

import java.util.HashSet;
import java.util.List;
import java.util.Map;

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
        for(Map.Entry v: myMap.entrySet()){
            System.out.println(v);
        }
       /* System.out.println("get die value: " + myMap.get("die"));
        System.out.println("get antwood value: " + myMap.get("antwood"));
        myMap.put("antwood",444);
        System.out.println("put antwood: " + myMap.put("antwood",444));*/

        assertEquals(4, myMap.size());

        assertFalse(myMap.isEmpty());
        myMap.remove("die");

        System.out.println("trying to remove: " + myMap.size());
        myMap.clear();
        System.out.println(myMap.size());
        assertTrue(myMap.isEmpty());
        /*assertEquals(true, myMap.containsValue(2222));*/
    }
    @Test
    void HashPrintTest(){
        HashMap<Integer, Integer> myMap = new HashMap<>();
        myMap.put(1,2);
        myMap.put(2,3);
        myMap.put(4,5);
        for(Map.Entry v: myMap.entrySet()){
            System.out.println(v);
        }
    }
}
