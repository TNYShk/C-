package il.co.ilrd.syncproblem;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SyncWriteingReading {
    private AtomicInteger cnt = new AtomicInteger(0);
    private final ReentrantLock lock = new ReentrantLock();


    public SyncWriteingReading(){}

    public void startWrite(){
        lock.lock();
        while(cnt.get() != 0);
    }

    public void endWrite(){
        lock.unlock();
    }

    public void startRead(){
        lock.lock();
        cnt.getAndIncrement();
        lock.unlock();

    }

    public void endRead(){
        cnt.getAndDecrement();
    }


}
