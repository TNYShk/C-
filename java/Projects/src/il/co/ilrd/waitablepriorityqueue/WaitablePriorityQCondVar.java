package il.co.ilrd.waitablepriorityqueue;

import java.util.Comparator;

import java.util.PriorityQueue;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQCondVar<E>{
    private final PriorityQueue<E> myQ;
    private final ReentrantLock lock;
    private static final int INITCAP = 11;
    private final Condition conditionalVar;
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
        lock = new ReentrantLock();
        conditionalVar = lock.newCondition();
    }

    public void enqueue(E element) throws InterruptedException {

        lock.lock();
        while(myQ.size() == MAXCAPACITY)
            conditionalVar.await();

        myQ.add(element);
        //System.out.println(Thread.currentThread().getName() + " Q'd here");
        conditionalVar.signal();
        lock.unlock();
    }

    //thread safe
    public E dequeue() throws InterruptedException {
        E deQ;

        lock.lock();
        while(isEmpty())
            conditionalVar.await();

        deQ = myQ.poll();
        //System.out.println(Thread.currentThread().getName() + " DQ'd there");
        conditionalVar.signal();
        lock.unlock();
        return deQ;
    }

    //thread safe
    public boolean remove(E element) throws InterruptedException {
        boolean found;

        lock.lock();
        while(myQ.isEmpty()){
            conditionalVar.await();
        }
        found = myQ.remove(element);
        /*if(found)
            System.out.println(Thread.currentThread().getName() + " removed everywhere");*/
        conditionalVar.signal();
        lock.unlock();

        return found;
    }

    public int size() {
        return myQ.size();
    }

    public boolean isEmpty() {
        return myQ.isEmpty();
    }

}
