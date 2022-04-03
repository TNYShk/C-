package il.co.ilrd.genericSll;

//import java.util.ArrayList;
import java.util.ConcurrentModificationException;
import java.util.Iterator;

import static org.junit.Assert.*;

public class TestGenSll {


    public static void main(String []args){

        //TestUno();
        GenericList<String> genlist = new GenericList<>();
        GenericList<String> stringList = new GenericList<>();
        assertTrue(genlist.isEmpty());
        genlist.pushFront("Hi");
        genlist.pushFront("my");
        genlist.pushFront("name");
        genlist.pushFront("is");
        genlist.pushFront("Slim Shady");
        System.out.println("size of list is " + genlist.size());
        printList(genlist);
        genlist = GenericList.newReverse(genlist);
        printList(genlist);



        Iterator<String> locate = null;
        locate = genlist.find("my");

        assertNotNull(locate);
        genlist = GenericList.newReverse(genlist);
        genlist.popFront();
        System.out.println("\npop front,size of list is " + genlist.size());



        locate = genlist.find("Slim Shady");
        assertNull(locate);

       genlist = GenericList.newReverse(genlist);
        System.out.println("printing in reverse");
        printList(genlist);
        genlist = GenericList.newReverse(genlist);

        stringList.pushFront("Who?");
        stringList.pushFront("My");
        stringList.pushFront("Name");
        stringList.pushFront("was");
        stringList.pushFront("What?");
        stringList.pushFront("U sure?!");
        stringList.pushFront("It's Britney B*tch!");
        System.out.println("size of another list is " + stringList.size());
        stringList = GenericList.newReverse(stringList);
        printList(stringList);

        System.out.println("Merging lists: ");
        try{
            stringList = GenericList.mergeLists(genlist,stringList);
        } catch(ConcurrentModificationException e){
            System.out.println("Lo NOra");

        }

        printList(stringList);
        System.out.println("size of merged list is now " + stringList.size());

        assertEquals(0,genlist.size());
        assertTrue(genlist.isEmpty());
       /* assertFalse(genlist.isEmpty());
        assertEquals(3,genlist.size());*/
        //TestStam();



    }
/*
    static void TestStam(){
        List<String> v = new ArrayList<>();
        v.add("hello");
        String s = v.get(0);
        System.out.println(s);
    }*/

    static void TestUno(){
        GenericList<String> stringList = new GenericList<>();
        assertTrue(stringList.isEmpty());
        stringList.pushFront("Who?");
        stringList.pushFront("my");
        stringList.pushFront("name");
        stringList.pushFront("is");
        stringList.pushFront("What?");
        stringList.pushFront("My name is?");
        System.out.println("size of list is " + stringList.size());
        printList(stringList);
        stringList = GenericList.newReverse(stringList);
        printList(stringList);
    }

    public static void printNumList(GenericList<? extends Number> list){
        assertFalse(list.isEmpty());
        for (Number s: list){
            System.out.print(s + " ");
        }
        System.out.println();
    }

    public static void printList(GenericList<String> list){
        assertFalse(list.isEmpty());
        for (String s: list){
            System.out.print(s + " ");
        }
        System.out.println();
    }
}
