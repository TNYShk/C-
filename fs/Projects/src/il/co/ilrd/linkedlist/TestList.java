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
        test.popFront();
        System.out.println(test.isEmpty());

    }
}

