package il.co.ilrd.syncproblem;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SyncReadWrite2 implements Runnable{
    static Semaphore sem;
    ReentrantLock lock;
    private final int MAX_READERS;
    static StringBuilder text = new StringBuilder();

    public SyncReadWrite2(int max_readers) {
        MAX_READERS = max_readers;
        this.sem = new Semaphore(max_readers);
        this.lock = new ReentrantLock();
    }

    public void startRead() throws InterruptedException {
        lock.lock();
        sem.acquire();
        lock.unlock();
    }

    public void read(){
        System.out.println(Thread.currentThread().getName() + " read "+ text);
    }

    public void endRead(){
        sem.release();
    }

    public void startWrite() throws InterruptedException {
        lock.lock();
        sem.acquire(MAX_READERS);
    }

    public void write(){
        System.out.println(Thread.currentThread().getName() + " wrote ");
        text.append("z");
    }

    public void endWrite(){
        sem.release(MAX_READERS);
        lock.unlock();
    }
/*
   the risk here is starvation of readers
*/
    public static void  main(String[] args){
        SyncReadWrite2 swr = new SyncReadWrite2(10);
        Thread[] readers = new Thread[10];
        Thread[] writers = new Thread[10];


        for(int i = 0; i< 10; ++i){
            readers[i] = new Thread(swr, "reader");
            writers[i] = new Thread(swr, "writer");

        }

        for(int i = 0; i< 10; ++i){
           writers[i].start();
            readers[i].start();
        }

    }

    @Override
    public void run() {
        if(Thread.currentThread().getName().equals("writer")){

            try {
                startWrite();
                write();
                endWrite();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

        }else{

            try {
                startRead();
                read();
                endRead();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

        }
    }
}
