package il.co.ilrd.genericSll;

//import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import static org.junit.Assert.*;

public class TestGenSll {


    public static void main(String []args){

        GenericList<String> genlist = new GenericList<>();
        genlist.pushFront("Hi");
        genlist.pushFront("my");
        genlist.pushFront("name");
        genlist.pushFront("is");
        genlist.pushFront("Slim Shady");
        System.out.println("size of list is " + genlist.size());

        for (String s: genlist){
            System.out.print(s + " ");
        }
        System.out.println();


        Iterator<String> locate = null;
        locate = genlist.find("my");

        assertTrue(locate != null);
        genlist.popFront();
        System.out.println("pop front,size of list is " + genlist.size());

        for (String s: genlist){
            System.out.print(s + " ");
        }
        System.out.println();

        locate = genlist.find("Slim Shady");
       assertEquals(null,locate);



        //TestStam();



    }
/*
    static void TestStam(){
        List<String> v = new ArrayList<>();
        v.add("hello");
        String s = v.get(0);
        System.out.println(s);
    }*/
}
