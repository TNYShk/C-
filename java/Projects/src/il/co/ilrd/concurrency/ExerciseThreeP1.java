package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicBoolean;



public class ExerciseThreeP1 implements Runnable{
    static AtomicBoolean globalAtomicBul = new AtomicBoolean();
    Semaphore sem1 = new Semaphore(1);
    Semaphore sem2 = new Semaphore(0);




    public void consume() throws InterruptedException {
        int count = 0;
        while( count < 10) {
            sem1.acquire();
            System.out.println("ping");
            ++count;

            sem2.release();
        }
    }
    public void consume1() throws InterruptedException {
        int count = 0;
        while( count < 10) {
            if ( !globalAtomicBul.get()) {
                System.out.println("ping");
                ++count;
                globalAtomicBul.compareAndSet(false, true);
            }

        }
    }


    public void produce() throws InterruptedException{
        int count = 0;
        while( count < 9) {
            sem2.acquire();
            System.out.println("pong");
            ++count;

        sem1.release();
        }
    }

    public void produce1() {
        int count = 0;
        while( count < 9) {
            if (globalAtomicBul.get()) {
                System.out.println("pong");
                ++count;
                globalAtomicBul.compareAndSet(true, false);
            }
        }
    }

    @Override
    public void run() {

        if (Thread.currentThread().getName().equals("consumer")) {
            try {
                System.out.println(Thread.currentThread().getName() + " " + java.time.LocalDateTime.now());
                consume();
                consume1();
            } catch (InterruptedException e) {
                    e.printStackTrace();
            }
        } else {
            try {
                System.out.println(Thread.currentThread().getName() + " " + java.time.LocalDateTime.now());
                produce();
                produce1();
            } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

        System.out.println(Thread.currentThread().getName() + " " + java.time.LocalDateTime.now());
    }




    public static void main(String[] args){

        ExerciseThreeP1 test = new ExerciseThreeP1();
        Thread consumer = new Thread(test, "consumer");
        Thread producer = new Thread(test, "producer");

        consumer.start();
        producer.start();
        try{
            consumer.join();
            producer.join();
        }catch (InterruptedException e){
            e.printStackTrace();
        }



    }



}
