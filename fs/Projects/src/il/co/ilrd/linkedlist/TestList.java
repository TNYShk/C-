package il.co.ilrd.linkedlist;

public class TestList {

    public static void main (String args[]){

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
            System.out.println("found  ");
        } else {
            System.out.println("Not found");
        }
        if ((null != test.find(7))) {
            System.out.println("found  ");
        } else {
            System.out.println("Not found");
        }


        test.popFront();
        test.popFront();
        System.out.println(test.isEmpty());

    }
}


