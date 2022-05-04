package il.co.ilrd.linkedlist;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

public class TestList {

    public static void main(String args[]) {


        JunitTest tanya = new JunitTest();




        testUno();
        testDos();

    }

    static void testUno() {
        Double d = 26.6;
        Double pi = 3.14;
        SinglyLinkedList test = new SinglyLinkedList();
        System.out.println("list is empty? " + test.isEmpty());
        System.out.println("trying to pop empty list..\n");
        test.popFront();
        System.out.println("trying to push into list..\n");
        test.pushFront(d);
        System.out.println("link size: " + test.listSize());

        test.pushFront(pi);
        System.out.println(test);
        System.out.println("link size: " + test.listSize());

        if ((null != test.find(d))) {
            System.out.println("found " + d);
        } else {
            System.out.println("Not found");
        }
        if ((null != test.find(7))) {
            System.out.println("found  ");
        } else {
            System.out.println("7 Not found");
        }

        test.popFront();
        test.popFront();
        System.out.println("list is empty? " + test.isEmpty());
        System.out.println("Test 1 complete\n");
    }

    static void testDos() {
        Double d = 26.6;
        Double pi = 3.14;
        SinglyLinkedList testTwo = new SinglyLinkedList();
        System.out.println("empty list?" + testTwo.isEmpty());
        System.out.println("size is " + testTwo.listSize());
        testTwo.pushFront(d);
        testTwo.pushFront(pi);
        testTwo.pushFront(370.3);
        System.out.println("size is " + testTwo.listSize());

        if ((null != testTwo.find(pi))) {
            System.out.println("found  " + pi);
        } else {
            System.out.println("Not found");
        }
        ListIterator found = testTwo.find(d);

        if (null != found) {
            System.out.println("found  " + d);
        } else {
            System.out.println("Not found");
        }
        if (found.hasNext()) {
            System.out.println("Iterator has next!");
        } else {
            System.out.println("Iterator has no next!");
        }
        Object last = found.next();

        System.out.println("last is "+ last);

        found = testTwo.find(270);
        if (found.hasNext()) {
            System.out.println("found  270" );
        } else {
            System.out.println("Not found");
        }



        System.out.println(testTwo);
        ListIterator getBegin = testTwo.begin();
        System.out.println("list begins with: " + getBegin.next());
        testTwo.popFront();
        testTwo.popFront();
        System.out.println("size is " + testTwo.listSize());
        System.out.println("Test 2 complete");
    }
}
 class JunitTest{
        private SinglyLinkedList myList = new SinglyLinkedList();

        private
        @Test
        void testEmptyNullSLL(){
            assertEquals(true,myList.isEmpty());
            assertNull((myList).popFront());

            System.out.println("equals and assert null done!\n");

        }

        @Test
     void flipTest(){
            myList.pushFront(1L);
            myList.pushFront(2L);
            myList.pushFront(3L);
            myList.pushFront(4L);
            myList.pushFront(5L);
        }
    }


