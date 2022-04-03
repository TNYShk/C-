package il.co.ilrd.genericSll;
   /*
    generic linked list, its data is generic.
    class Node should be generic, since it holds the data (generic), also constructor needed.
    class Iterator, use java iterator interface! class linkedList implements Iterable (has Iterator method, similar to begin().)
    methods: size, pushFront,PopFront,isEmpty, find
    new methods: newReverse(List<T>) returns reversed list
    merge(LinkedList l1, LinkedList l2), merges lists together in any order. return the new merged list.
    use enhanced loop
    Iterator type failfast iterator java- read it!
     */



import java.util.Iterator;


public class GenericList<E> implements Iterable<E>  {
    private Node<E> head = null;
    private long version = 0;

    public void pushFront(E data) {
        ++version;
    }

    public E popFront() {
        ++version;

        return null;}

    public int size() {
        int count = 0;

        for(E GenericList : this){
            ++count;
        }
        return count;
    }

    public boolean isEmpty() {
        return (head == null);
    }

    public Iterator<E> find(E data) {
        ListIteratorIMP run = new ListIteratorIMP(head);
        for(E GenericList: this){
            if(data.equals(run)){
                return run;
            }run.next();
        }
        return null;
    }

    public static <T> GenericList<T> newReverse(GenericList<T> list) {
        return null;}

    public static <T> GenericList<T> merge(GenericList<T> list1, GenericList<T> list2) {
        return null;}

    @Override
    public Iterator<E> iterator() {
       ++version;
       return new ListIteratorIMP(head);
    }

    private static class Node<T> {

        private T data = null;
        private Node<T> next = null;

        private Node(T data, Node<T> next){
            this.data = data;
            this.next = next;
        }
    }

    private class ListIteratorIMP implements Iterator<E>{
    private Node<E> currentNode = null;
    private final long controlVersion = version;

   private ListIteratorIMP(Node<E> node){
    currentNode = node;
   }
    @Override
    public boolean hasNext() {
        return ((null != currentNode) );
    }

    @Override
    public E next() {
       E thisData = null;

       return null;
    }
}





    }
