package il.co.ilrd.concurrency;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class ExerciseTwo implements Runnable {
    static int globalCounter = 0;
    static AtomicInteger globalAtomicCounter = new AtomicInteger(0);
    static ReentrantLock lock = new ReentrantLock();


    public void countToAlot() {
        {
            synchronized (this) {
                for (int i = 0; i < 10000000; ++i) {
                    ++globalCounter;
                }
                System.out.println(java.time.LocalDateTime.now() + " global sync block " + Thread.currentThread().getName()+ " count: \n" +globalCounter);
            }
        }
    }

    public synchronized void countAlot() {
        for (int i = 0; i < 10000000; ++i) {
            ++globalCounter;
        }
        System.out.println(java.time.LocalDateTime.now() + " global sync method " + Thread.currentThread().getName() + " count: \n" +globalCounter);

    }
    public void LockcountAlot() {
        lock.lock();
        for (int i = 0; i < 10000000; ++i) {
            ++globalCounter;
        }
            System.out.println(java.time.LocalDateTime.now() + Thread.currentThread().getName() + " global count: \n" +globalCounter );

        lock.unlock();
    }

    public void notSyncAtomicCount(){
        for (int i = 0; i < 10000000; ++i) {
            globalAtomicCounter.addAndGet(1);
        }
        System.out.println(java.time.LocalDateTime.now() + " Atomic " + Thread.currentThread().getName() + " count:\n" + globalAtomicCounter);

    }

    public synchronized void SyncAtomicCount(){
        for (int i = 0; i < 10000000; ++i) {
            globalAtomicCounter.addAndGet(1);
        }
        System.out.println(java.time.LocalDateTime.now() + " Atomic  " + Thread.currentThread().getName() + " count:\n" + globalAtomicCounter);
    }




    @Override
    public void run() {

        /*
        countToAlot();
        countAlot();
        LockcountAlot();
        notSyncAtomicCount();

        */
        SyncAtomicCount();

    }

    public static void main(String[] args){
        ExerciseTwo next = new ExerciseTwo();

        Thread one = new Thread(next);
        Thread two = new Thread(next);

        one.start();
        two.start();
        try{
            one.join();
            two.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        //System.out.println("counter "+ ExerciseTwo.globalCounter);
    }
}

