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


}
