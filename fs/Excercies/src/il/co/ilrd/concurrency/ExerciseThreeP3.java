package il.co.ilrd.concurrency;


import java.util.concurrent.Semaphore;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ExerciseThreeP3 implements Runnable {
    private volatile int message = 0;
    final Lock lock = new ReentrantLock();
    static Semaphore sem = new Semaphore(0);
    final Condition notReady = lock.newCondition();
    final int numOfConsumers = 3;

    private void produce() throws InterruptedException {
        for (int j = 0; j < 5; ++j) {
            sem.acquire(numOfConsumers);
            message += 1;
            lock.lock();
            notReady.signalAll();
            lock.unlock();
        }
    }

    public void consume() throws InterruptedException {
        for (int j = 0; j < 5; ++j) {
            lock.lock();
            sem.release();
            notReady.await();
            System.out.println(Thread.currentThread().getName() + " consumed " + message);
            lock.unlock();
        }
    }

    @Override
    public void run() {
            if (Thread.currentThread().getName().equals("producer")) {
                try {
                    //System.out.println(Thread.currentThread().getName() + " " + java.time.LocalDateTime.now());
                    produce();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } else {
                try {
                    //System.out.println(Thread.currentThread().getName() + " " + java.time.LocalDateTime.now());
                    consume();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

    public static void main(String args[]){
        ExerciseThreeP3 ex3 = new ExerciseThreeP3();
        Thread producer = new Thread(ex3, "producer");
        producer.start();

        for(int i = 0; i< ex3.numOfConsumers; ++i){
            Thread consumer = new Thread(ex3);
            consumer.start();
        }


    }
}
