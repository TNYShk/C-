package il.co.ilrd.complex.hashMap;

import java.util.HashSet;
import org.junit.jupiter.api.Test;
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
        assertFalse(pp4.hashCode()== pp3.hashCode());
        assertTrue(Pair.swap(pp5).equals(pp4));

    }
    @Test
    void TestArry(){
        Double[] darry = {1.2,3.2,-5.1,4.4, 0.0, -99.9};
        Pair<Double,Double> pd3 = Pair.minMax(darry);
        assertTrue(Pair.of(-99.9,4.4).equals(pd3));
    }

    @Test
    void TestString(){
        String[] strArry = {"aaaa","one", "two", "three","four","zzz" };
        Pair<String,String> s1 = Pair.minMax(strArry,String::compareTo);
        assertTrue(s1.getKey().equals("aaaa"));
        assertTrue(s1.getValue().equals("zzz"));
    }



}
