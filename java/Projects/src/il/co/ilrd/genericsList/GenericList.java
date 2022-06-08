package il.co.ilrd.genericsList;

import java.util.ConcurrentModificationException;
import java.util.Iterator;


public class GenericList<E> implements Iterable<E> {
    private Node<E> head = null;
    private long version = 0;

    public void pushFront(E data) {
        ++version;
        head = new Node<>(data,head);

    }

    public E popFront() {
        E dataToRemove = head.data;
        head = head.next;
        ++version;
        return dataToRemove;
    }
    //E list isnt used, forEach count
    @SuppressWarnings("unused parameterized type ")
    public int size() {
        int count = 0;

        for(E list  : this){

            ++count;
        }
        return count;
    }

    public boolean isEmpty() {
        return (head == null);
    }

    public Iterator<E> find(E data) {

      for (E element : this) {
            if (element.equals(data)) {
                Node<E> node = new Node<>(element, null);
                return new ListIteratorIMP(node);
            }
        }
        return null;

       /*  Iterator<E> iter = iterator();
        Iterator<E> prevIter = iterator();
        while(iter.hasNext() && !iter.equals(data)){
            iter.next();
        }
        return prevIter;*/
    }

    public static <T> GenericList<T> newReverse(GenericList<T> list) {
        GenericList<T> reversedList = new GenericList<>();

        for(T data : list){
            reversedList.pushFront(data);
        }
        return reversedList;
    }

    public static <T> GenericList<T> mergeLists(GenericList<T> list1, GenericList<T> list2) {
        GenericList<T> mergedList = new GenericList<>();

        for(T data : list2) {
            mergedList.pushFront(data);
        }
        for(T data : list1){
            mergedList.pushFront(data);
        }
        return mergedList;
    }

    @Override
    public Iterator<E> iterator() {
       return new ListIteratorIMP(head);
    }
//node is a static class doesnt need anything from the enclosing class a stand alone and for safety so it wont change something
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
    public E next()  {
       E thisData = null;

        if(controlVersion != version) {
            throw new ConcurrentModificationException("hmmmm");
        }

        thisData = currentNode.data;
        currentNode = currentNode.next;
        return thisData;
    }
}





    }
