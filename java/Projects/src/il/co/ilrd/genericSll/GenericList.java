package il.co.ilrd.genericSll;



import java.util.ConcurrentModificationException;
import java.util.Iterator;


public class GenericList<E> implements Iterable<E>  {
    private Node<E> head = null;
    private long version = 0;

    public void pushFront(E data) {
        ++version;
        this.head = new Node<>(data,this.head);
    }

    public E popFront() {
        ++version;
        E dataToRemove = null;
        if(!isEmpty()){
            dataToRemove = head.data;
            this.head = head.next;
        }
        return dataToRemove;
    }

    public int size() {
        int count = 0;

        for(E list : this){
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
                Node<E> node = new Node<>(element, this.head.next);
                return new ListIteratorIMP(node);
            }
        }
        return null;
    }



    public static <T> GenericList<T> newReverse(GenericList<T> list) {
    GenericList<T> reversedList = new GenericList<>();
    for(T data : list){
        reversedList.pushFront(data);
    }
        return reversedList;}

    public static <T> GenericList<T> mergeLists(GenericList<T> list1, GenericList<T> list2) {
        for(T data : list1){
            list2.pushFront(list1.popFront());
            /*list2.pushFront(data);*/

        }
        return list2;}

    @Override
    public Iterator<E> iterator() {
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
    public E next()  {
       E thisData = null;
    /*assertEquals(controlVersion,version);*/
    try{
        if(controlVersion != version) {
            throw new ConcurrentModificationException();
        }

    }catch(ConcurrentModificationException e){
        System.err.println(e);
      e.printStackTrace();

    }
        thisData = currentNode.data;
        currentNode = currentNode.next;
        return thisData;
    }
}





    }
