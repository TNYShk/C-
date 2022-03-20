package il.co.ilrd.linkedlist;

public interface ListIterator {

    public boolean hasNext();
    public default Object next() {}
}
