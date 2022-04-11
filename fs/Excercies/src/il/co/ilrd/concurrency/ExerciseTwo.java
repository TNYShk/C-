package il.co.ilrd.concurrency;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class ExerciseTwo implements Runnable {
    static volatile int globalCounter = 0;
    static AtomicInteger globalAtomicCounter = new AtomicInteger();
    static ReentrantLock lock = new ReentrantLock();


    public void countToAlot() {
        {
            synchronized (this) {

                for (int i = 0; i < 10000000; ++i) {
                    ++globalCounter;
                }
                System.out.println(java.time.LocalDateTime.now() + " here in  " + Thread.currentThread().getName());
            }
        }
    }

    public synchronized void countAlot() {

        for (int i = 0; i < 10000000; ++i) {
            ++globalCounter;
        }
        System.out.println(java.time.LocalDateTime.now() + " here in  " + Thread.currentThread().getName());

    }
    public  void LockcountAlot() {
        lock.lock();
        for (int i = 0; i < 10000000; ++i) {
            ++globalCounter;
        }
            System.out.println(java.time.LocalDateTime.now() + " here in locked  " + Thread.currentThread().getName());
            System.out.println("counter "+ globalCounter);
        lock.unlock();


    }

    public  void notSyncAtomicCount(){
        for (int i = 0; i < 10000000; ++i) {
            globalAtomicCounter.addAndGet(1);
        }

        System.out.println(java.time.LocalDateTime.now() + " Atomic in  " + Thread.currentThread().getName() + " count:\n" + globalAtomicCounter);
    }

    public synchronized void SyncAtomicCount(){
        for (int i = 0; i < 10000000; ++i) {
            globalAtomicCounter.addAndGet(1);
        }
        System.out.println(java.time.LocalDateTime.now() + " Atomic in  " + Thread.currentThread().getName() + " count:\n" + globalAtomicCounter);
    }


    @Override
    public void run() {
        //System.out.println(java.time.LocalDateTime.now() + " "+ Thread.currentThread().getName());
       /* countToAlot();
        countAlot();*/
        //notSyncAtomicCount();
        //SyncAtomicCount();
        LockcountAlot();
    }
}

