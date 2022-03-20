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
            currentNode = currentNode.next;
            return currentNode.data;
        }

        @Override
        public boolean hasNext(){
            return this.currentNode.data != null;
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

        while(null != runner) {
            if(runner.data.equals(data)){
               return new ListIteratorImp(runner);
            }
            runner = runner.next;
        }
       return holder;
    }

    public ListIterator begin() {
        ListIterator headbanger = new ListIteratorImp(this.head);
        return headbanger;
    }



}

