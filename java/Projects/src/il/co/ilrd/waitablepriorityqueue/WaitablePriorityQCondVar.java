package il.co.ilrd.waitablepriorityqueue;

import java.util.Comparator;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQCondVar<E> {
    private PriorityQueue<E> myQ;
    private final ReentrantLock lock = new ReentrantLock();
    private static final int INITCAP = 11;

    private final Condition conditionalVar = lock.newCondition();
    private final int MAXCAPACITY;

    public WaitablePriorityQCondVar(int maxcapacity) {
        this(null,INITCAP,maxcapacity);
    }

    public WaitablePriorityQCondVar(int initialCapacity, int maxcapacity) {
        this(null,initialCapacity, maxcapacity);
    }

    public WaitablePriorityQCondVar(Comparator<? super E> compare, int maxcapacity) {
        this(compare,INITCAP, maxcapacity);

    }

    public WaitablePriorityQCondVar(Comparator<? super E> compare, int initialCapacity, int maxcapacity) {
        if(maxcapacity < INITCAP){
            maxcapacity = INITCAP;}

        MAXCAPACITY = maxcapacity;
        myQ =  new PriorityQueue<>(initialCapacity, compare);
    }

    //thread safe
    public void enqueue(E element) throws InterruptedException {

        lock.lock();
        myQ.add(element);
        conditionalVar.signalAll();
        lock.unlock();
    }

    //thread safe
    public E dequeue() throws InterruptedException {
        E deQ;

        lock.lock();
        conditionalVar.await();
        deQ = myQ.poll();
        lock.unlock();
        return deQ;
    }

    //thread safe
    public boolean remove(E element) {
        boolean found  = false;
        if(myQ.contains(element)){
            for(Iterator<E> iter = myQ.iterator(); iter.hasNext(); iter.next()){
                if(iter.equals(element)){
                    lock.lock();
                    iter.remove();
                    found = true;
                    lock.unlock();
                }
            }
        }
        return found;
    }

    public int size() {
        return myQ.size();
    }

    public boolean isEmpty() {
        return myQ.isEmpty();
    }

}
