package il.co.ilrd.linkedlist;

public class SinglyLinkedList {
    private Node head = null;

    //default constructor

    private class Node {
        private Object data = null;
        private Node next = null;

        private Node(Object data, Node next){
            this.data = data;
            this.next = next;
        }
    }

    private class ListIteratorImp implements ListIterator {
        private Node currentNode = null;

        private ListIteratorImp (Node head) {
            currentNode = head;
        }

        @Override
        public Object next() {
            Object nextData = currentNode;

            if(null != currentNode){
                nextData = currentNode.data;
                currentNode = currentNode.next;
            }
            return nextData;
        }

        @Override
        public boolean hasNext(){
            return ((null != currentNode) && (null != currentNode.next));
        }
    }

    public void pushFront(Object data) {
        Node newNode = new Node(data , this.head);
        this.head = newNode;
        System.out.println("pushed to list: " + data);
    }

    public Object popFront() {
        Object removedData = null;

        if(!isEmpty()) {
            removedData = this.head.data;
            this.head = head.next;
        }
    return removedData;
    }

    public int listSize() {
        int count = 0;
        Node runner = head;
            while(null != runner){
               ++count;
               runner = runner.next;
            }
        return count;
        }

    public boolean isEmpty(){
        return (head == null);
    }

    public ListIterator find(Object data) {
        Node runner = this.head;
        ListIterator holder = null;

        while((null != runner) ){
            if(runner.data.equals(data)){
                holder = new ListIteratorImp(runner);
            }
            runner = runner.next;
        }
       return holder;
    }

    public ListIterator begin() {
        ListIterator headbanger = new ListIteratorImp(this.head);
        return headbanger;
    }

    @Override
    public String toString() {
        Node runner = this.head;
        String list = "List elements:\n{ " ;
        while (null != runner) {
            list += runner.data + " ";
            runner = runner.next;
        }

        list += "}";

        return list;
    }


}
<<<<<<< HEAD
=======

>>>>>>> d77c11b7bc622e767cad44fcbd20f005bed25c92
