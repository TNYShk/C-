package il.co.ilrd.linkedlist;

public class SingltLinkedList {
    private Node head = null;

    //default constructor
    public void pushFront(Object data) {}
    public Object popFront() {}
    public int size() {}
    public boolean isEmpty() {}
    public ListIterator find(Object data) {}
    public ListIterator begin() {}

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
            this.currentNode = this.currentNode.next;
            return currentNode.data;
        }

        @Override
        public boolean hasNext(){
            return this.currentNode.data != null;
        }
    }

}
