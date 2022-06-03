package il.co.ilrd.quiz_genericsll;

import java.util.Iterator;

public class GenericLinkedList<T> implements Iterable<T>{
    private Node<T> head;
    private int version = 1;

    @Override
    public Iterator<T> iterator() {
        return new GenListIterator(head);
    }

    static class Node<T>{
        private T data;
        private Node<T> next;

        private Node(T t, Node<T> next){
            data = t;
            this.next = next;
        }

        public Node(T t){
            this.data = t;
            this.next = null;
        }
    }
    private class GenListIterator implements Iterator<T>{
    protected Node<T> current;
    private final int curVersion = version;
        public GenListIterator(Node<T> node){
            current = node;
        }
        public GenListIterator(){
            current = head;
        }

        @Override
        public boolean hasNext() {
           return current != null;
        }

        @Override
        public T next() {
            T data = null;
            if((version == curVersion)){
                data = current.data;
                current = current.next;
            }else{
                System.out.print("ConcurrentModificationException!");
            }
           return data;
        }

        @Override
        public String toString(){
            return "" +current.data;
        }
    }

    public boolean isEmpty(){
        return this.head == null;
    }

    public void pushFront(T t){
        head = new Node<>(t,head);
        ++version;
    }
    public T popFront(){
       T t = head.data;
        ++version;
        if(!this.isEmpty()) {
            head = head.next;
        }
        return t;
    }

    public int size(){
        int counter = 0;
        Iterator<T> runner = new GenListIterator();
        for( ; runner.hasNext();runner.next())
                ++counter;
        return counter;
    }
    public Iterator<T> find(T t){
       for(T find: this){
           if(find.equals(t))
               return new GenListIterator(new Node<>(t));
       }
       return null;
    }

    public String toString(){
        return "" +head.data;
    }

    public void reverseList(){

        if(head != null)
            head = reverseList(null, head);
    }

    private Node<T> reverseList(Node<T> parent, Node<T> child){
        Node<T> runner = child.next;
        child.next = parent;
        return(runner == null)?child : reverseList(child, runner);

    }

    public void printGenList(){
        for(T t: this){
            System.out.print(t.toString() + " ");
        }
        System.out.println();
    }

    public void flipList(){
        Node<T>runner = head;
        Node<T> prev = null;
        Node<T> next = null;

       while(runner != null){
          next = runner.next;
          runner.next = prev;
          prev = runner;
          runner = next;
        }
       head = prev;
    }
    public T getNthFromEnd(int n){
        if(n <= this.size()){
            reverseList();
            Iterator<T> runner = new GenListIterator(head);

            while(--n > 0){
                runner.next();
            }
            reverseList();
            return runner.next();
        }
        return null;
    }

    public void circularShiftInPlace(int n){

        reverseShift(0,this.size()-1);
        reverseShift(0,n-1);
        reverseShift(n,this.size()-1);
    }

    private void reverseShift(int from, int to){
        while(from<to) {
            Swap(from, to);
            ++from;
            --to;
        }
    }

    private void Swap( int from, int to){
        Node<T> runner = head;
        Node<T> Trunner = head;
        for(int i= 0; i<from; ++i){
            runner = runner.next;
        }
        T Fdata = runner.data;
        for(int i= 0; i<to; ++i){
            Trunner = Trunner.next;
        }
        runner.data = Trunner.data;
        Trunner.data = Fdata;

        }



}
