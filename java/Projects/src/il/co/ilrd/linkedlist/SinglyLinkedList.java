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
            Object nextData = null;

            if(null != currentNode){
                nextData = currentNode.data;
                currentNode = currentNode.next;
            }
            return nextData;
        }

        @Override
        public boolean hasNext(){
            return ((null != currentNode) );
        }
    }

    public void pushFront(Object data) {
        Node newNode = new Node(data, this.head);
       head = newNode;

    }

    public Object popFront() {
        Object removedData = null;

        if(!isEmpty()) {
            removedData = head.data;
            head = head.next;
        }
    return removedData;
    }
    /*

// don't punish good users with if (is empty..)
    public Object popFront() {
        Object removedData = head.data;
        head = head.next;
        return removedData;
    }
*/



    public int listSize() {
        int count = 0;
        ListIteratorImp run = new ListIteratorImp(head);

        while(run.hasNext()){
            ++count;
            run.next();
        }
        Integer c = count;

        return count;

        }



    public boolean isEmpty(){
        return (head == null);
    }

    public ListIterator find(Object data) {

        ListIteratorImp run = new ListIteratorImp(head);

        while(run.hasNext() && !(run.currentNode.data.equals(data))){
                run.next();
            }
        return run;
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
