package il.co.ilrd.waitablepriorityqueue;

import java.util.Comparator;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueueSem<E> {
    private PriorityQueue<E> myQ ;
    private Semaphore sem ;
    private final ReentrantLock lock = new ReentrantLock();
    private static final int INITCAP = 11;

    //private condition var cond1
    private final int MAXCAPACITY;

    public WaitablePriorityQueueSem(int maxcapacity) {
        this(null,INITCAP,maxcapacity);
    }

    public WaitablePriorityQueueSem(int initialCapacity, int maxcapacity) {
        this(null,initialCapacity, maxcapacity);
    }

    public WaitablePriorityQueueSem(Comparator<? super E> compare, int maxcapacity) {
       this(compare,INITCAP, maxcapacity);

    }

    public WaitablePriorityQueueSem(Comparator<? super E> compare, int initialCapacity, int maxcapacity) {
        if(maxcapacity < INITCAP){
            maxcapacity = INITCAP;}

        MAXCAPACITY = maxcapacity;
        myQ =  new PriorityQueue<>(initialCapacity, compare);
        sem = new Semaphore(MAXCAPACITY);
    }

    //thread safe
    public void enqueue(E element) throws InterruptedException {
        sem.acquire();
        //lock.lock();
        myQ.add(element);
        //lock.unlock();
    }

    //thread safe
    public E dequeue() {
        E deQ;
        sem.release();
        lock.lock();
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
                    sem.release();
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


