package il.co.ilrd.generics;


import org.testng.annotations.Test;

import java.util.ArrayList;
import java.util.List;



import static org.testng.AssertJUnit.assertFalse;

public class JewInTest {

    @Test
    void warningTest(){
        List<Number> byy = new ArrayList<>();
        for(int i= 0; i<15; ++i){
            byy.add(i, i*i);
        }
        ItemTwentySeven<Number> test = new ItemTwentySeven<>(byy);
        assertFalse(test.equals(byy));
        test.toArray(byy.toArray());
        System.out.println(test);
        System.out.println(byy);
    }
}
