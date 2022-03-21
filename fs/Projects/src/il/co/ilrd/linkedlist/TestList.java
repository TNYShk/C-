package il.co.ilrd.linkedlist;

public class TestList {

    public static void main (String args[]){
        testUno();
        testDos();

    }

    static void testUno(){
        Double d = 26.6;
        Double pi = 3.14;
        SinglyLinkedList test = new SinglyLinkedList();
        System.out.println(test.isEmpty());

        test.pushFront(d);
        System.out.println(test.isEmpty());

        System.out.println(test.isEmpty());
        test.pushFront(pi);
        System.out.println(test.listSize());

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
        System.out.println(test);

        test.popFront();
        test.popFront();
        System.out.println("post pop, empty?" + test.isEmpty());
        System.out.println("Test 1 complete\n");
    }

    static void testDos(){
        Double d = 26.6;
        Double pi = 3.14;
        SinglyLinkedList testTwo = new SinglyLinkedList();
        System.out.println("List empty?" + testTwo.isEmpty());
        System.out.println("size is " + testTwo.listSize());
        testTwo.pushFront(d);
        testTwo.pushFront(pi);
        testTwo.pushFront(370.3);
        System.out.println("size is " + testTwo.listSize());

        if ((null != testTwo.find(pi))) {
            System.out.println("found  "+ pi);
        } else {
            System.out.println("Not found");
        }
        ListIterator found = testTwo.find(d);

        if (null != found){
            System.out.println("found  " + d);
        } else {
            System.out.println("Not found");
        }
        if(found.hasNext()){
            System.out.println("Iterator has next!");
            } else{
                System.out.println("Iterator has no next!");
            }
        System.out.println(testTwo);
        found = testTwo.find(750);
        if (null != found){
            System.out.println("found!");
        } else {
            System.out.println("750 isnt there");
        }
        ListIterator getBegin =  testTwo.begin();
        System.out.println("list begins with: "+ getBegin.next());

        testTwo.popFront();
        testTwo.popFront();
        System.out.println("size is " + testTwo.listSize());
        System.out.println("Test 2 complete");
    }
}

