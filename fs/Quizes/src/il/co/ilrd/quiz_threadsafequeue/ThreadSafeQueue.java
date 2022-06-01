package quiz_threadsafequeue;

import il.co.ilrd.quiz11_12_syncproblem.FizzBuzzThread;
import il.co.ilrd.quiz11_12_syncproblem.NumberThread;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ThreadSafeQueue<E> {
    private E element;
    private Deque<E> dq ;
    private Lock deq;
    private Lock Enq;
    private AtomicInteger counter = new AtomicInteger();
    private final int capacity;

    public ThreadSafeQueue(int cap){
        if (cap<16){
            cap = 16;
        }
        this.capacity = cap;
        dq = new ArrayDeque<>(capacity);
        deq = new ReentrantLock();
        Enq = new ReentrantLock();
    }
    public void enqueue(E element){
        if(dq.size()< capacity){
            Enq.lock();
            dq.addFirst(element);
            counter.getAndIncrement();
            Enq.unlock();
        }
    }

    public E dequeue(){
        E elem = null;
        if(counter.get() >1){
            deq.lock();
            elem = dq.pollLast();
            counter.getAndDecrement();
            deq.unlock();
        }
        return elem;
    }

    public void printValues(){
        for(E e : dq){
            System.out.print(e + " ");
        }
    }
}
class Testing{

    private static final int limit = 26;

    //private static ThreadSafeQueue<Integer> fsq = new ThreadSafeQueue<>(limit);

    public static void main(String[] args) {
        ThreadSafeQueue<Integer> fsq = new ThreadSafeQueue<>(limit);

        Thread t1 = new Thread(()->{
            for(int i = 0; i < limit; ++i) {
                fsq.enqueue(i);
               try {
                    Thread.sleep(500);
              } catch (InterruptedException e) {
                   throw new RuntimeException(e);
                }
            }
        });

        Thread  t2 = new Thread(()->{
            for(int i = 0; i < limit; ++i){
                System.out.println(fsq.dequeue());
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                fsq.enqueue(2 * i);
            }

        });

        t1.start();
        t2.start();

        fsq.printValues();
    }
}
