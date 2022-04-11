package il.co.ilrd.genericsList;

//import java.util.ArrayList;
import java.util.ConcurrentModificationException;
import java.util.Iterator;

import static org.junit.Assert.*;

public class TestGenSll {


    public static void main(String []args){


        TestUno();
        TestDos();
    }
/*
    static void TestStam(){
        List<String> v = new ArrayList<>();
        v.add("hello");
        String s = v.get(0);
        System.out.println(s);
    }*/

    static void TestUno(){
        GenericList<Number> numList = new GenericList<>();
        assertTrue(numList.isEmpty());
        numList.pushFront(3.14);
        numList.pushFront(4);
        numList.pushFront(0.005);
        numList.pushFront(3);
        numList.pushFront(4);
        numList.pushFront(2022);
        assertEquals(6,numList.size());
        printNumList(numList);
        Iterator<?> brr = null;
        brr = numList.find(3.15);
        Iterator<?> fond = null;
        fond = numList.find(3.14);
        assertNotEquals(brr,fond);

        numList = GenericList.newReverse(numList);
        printNumList(numList);
        assertEquals(6,numList.size());

        numList.popFront();
        numList.popFront();
        numList.popFront();
        numList.popFront();
        numList.popFront();
        numList.popFront();

        assertTrue(numList.isEmpty());
        assertEquals(0,numList.size());
        System.out.println("End test 1\n");

    }
    static void TestDos(){
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

        assertEquals(4,genlist.size());
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
            e.printStackTrace();

        }

        printList(stringList);
        System.out.println("size of merged list is now " + stringList.size());

        assertEquals(4,genlist.size());
        assertFalse(genlist.isEmpty());

        //TestStam();


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
