package il.co.ilrd.concurrency;


import java.util.concurrent.Semaphore;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumer implements Runnable{
    private volatile int message = 0;
    final Lock lock = new ReentrantLock();
    static Semaphore sem = new Semaphore(1);
    final Condition notReady = lock.newCondition();
    final int numOfConsumers = 3;




    private void produce() throws InterruptedException {
        while (true) {
            sem.acquire(numOfConsumers);
            lock.lock();
            message += 1;
            notReady.signalAll();
            lock.unlock();
        }
    }

    public void consume() throws InterruptedException{
        while(true) {
            lock.lock();
            sem.release();
            notReady.await();
            System.out.println(Thread.currentThread().getName() + " consumed " + message);
            lock.unlock();
        }
    }


    @Override
    public void run() {

            if (Thread.currentThread().getName() == "producer") {
                try {
                    produce();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } else {
                try {
                    consume();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

    public static void main(String args[]){
        ProducerConsumer ex3 = new ProducerConsumer();
        Thread producer = new Thread(ex3);
        producer.setName("producer");
        producer.start();

        for(int i = 0; i< ex3.numOfConsumers; ++i){
            Thread consumer = new Thread(ex3);
            consumer.start();
        }

    }
}
