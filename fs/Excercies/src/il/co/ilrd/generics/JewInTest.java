package il.co.ilrd.generics;


import org.testng.annotations.Test;

import java.util.*;


import static com.google.common.collect.ImmutableSet.of;
import static com.google.common.collect.Sets.union;
import static java.util.Set.*;
import static org.testng.AssertJUnit.*;


/*
   - Eliminate every possible unchecked Warning! (IDE, refactor code..)
        no warnings ==  typesafe code! no ClassCastException!
        generic introduces warnings:
        * unchecked cast warnings
        * unchecked method invocation
        * unchecked parameterized type
        * unchecked conversion warnings

    -Always use the @SuppressWarnings annotation on the smallest scope possible!
    -It is illegal to put a SuppressWarnings annotation on the return statement.
    -Every time you use a @SuppressWarnings("unchecked") annotation, add
    a comment saying why it is safe to do so.
        never ignore warnings, if new appear - might miss them..
 */



public class JewInTest {

    @Test
    void warningTest(){
        List<Number> byy = new ArrayList<>();
        Collection<Double> str = new ArrayList<>(15);

        for(int i= 0; i<15; ++i){
            byy.add(i, i*i);
            str.add((double) i * i);
        }

        ItemTwentySeven<Number> test = new ItemTwentySeven<>(byy);

        test.toArray(str.toArray());
        assertFalse(test.equals(byy));

        assertEquals(test.hashCode(),byy.hashCode() );

        assertNotSame(str.hashCode(),byy.hashCode() );
        assertEquals(str.size(), byy.size());
        System.out.println(test);
        System.out.println(byy);
        System.out.println("str: " + str);

        //error, incompatible types
    /* @SuppressWarnings("unchecked") boolean b =
              str.addAll((Collection<? extends Double>) byy);*/

    }



    public static void main(String[] args){
        Set<String> children = of("Maya","Adam");
        Set<String> animals = of("Twinky","Kika");
        children.forEach(s -> System.out.print(s + " "));
        Set<String> parents = of("Tanya","Igal");
        Set<String> famShkolnik = new HashSet<>();
        famShkolnik.add(String.valueOf(children));
        famShkolnik.add(String.valueOf(animals));
        famShkolnik.add(String.valueOf(parents));
        System.out.println("\n" + famShkolnik);
    }

}
