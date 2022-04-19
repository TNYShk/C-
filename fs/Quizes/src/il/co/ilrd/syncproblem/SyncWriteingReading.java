package il.co.ilrd.syncproblem;

import java.awt.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import static java.lang.Thread.sleep;
/*
multiple readers & writers
when a reader reads
    other readers can read
    writers CAN'T write!
when a writer writers
    readers CAN'T read
    other writers CAN'T write

may use only 1 atomic counter and 1 mutex
 */

public class SyncWriteingReading implements Runnable {
    private AtomicInteger cnt = new AtomicInteger(0);
    private final ReentrantLock lock = new ReentrantLock();
    static StringBuilder text = new StringBuilder();

    public SyncWriteingReading() {}

    public void startWrite() {
        lock.lock();
        while (cnt.get() != 0) ;
    }

    public static void write() {
        System.out.println(Thread.currentThread().getName() + " wrote ");
        text.append("w");
    }

    public void endWrite() {
        lock.unlock();
    }

    public void startRead() {
        lock.lock();
        cnt.getAndIncrement();
        lock.unlock();
    }

    public static void read() {
        System.out.println(Thread.currentThread().getName() + " read " + text);
    }

    public void endRead() {
        cnt.getAndDecrement();
    }

    @Override
    public void run() {

        if (Thread.currentThread().getName().equals("writer")) {
            System.out.println("he");
            startWrite();
            write();
            endWrite();
        } else {
            System.out.println("ha");
            startRead();
            read();
            endRead();
        }
    }
    /*
        the risk here is deadlock
     */
    public static void main(String[] args) throws InterruptedException {

        SyncWriteingReading swr = new SyncWriteingReading();

        Thread[] readers = new Thread[5];
        Thread[] writers = new Thread[5];

        for (int i = 0; i < 5; ++i) {
            writers[i] = new Thread(swr, "writer");
            readers[i] = new Thread(swr, "reader");
        }

        for (int i = 0; i < 5; ++i) {
            writers[i].start();
            readers[i].start();
        }


        for (int i = 0; i < 5; ++i) {
            writers[i].join();
            readers[i].join();
        }
        System.out.println("in main");
    }
}


