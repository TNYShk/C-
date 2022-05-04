package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class ZeroEvenOdd {
    private final int n;
    AtomicInteger nInt;
    Semaphore semZero;
    Semaphore semOdd;
    Semaphore semEven;
    static volatile boolean isEven = false;

    public ZeroEvenOdd(int n) {
        this.n = n;
        semZero = new Semaphore(1);
        semEven = new Semaphore(0);
        semOdd = new Semaphore(0);
        nInt = new AtomicInteger(0);
    }

    public void zero() throws InterruptedException {
        while(nInt.get() < n){
            semZero.acquire();
            System.out.print("0");
            nInt.getAndAdd(1);

            if(isEven){
                semEven.release();
                isEven = false;
            }
            else{
                semOdd.release();
                isEven = true;
            }
        }
    //throw new InterruptedException("zero enough");
    }

    public void even() throws InterruptedException {
        while(nInt.get() < n){
            semEven.acquire();
            System.out.print(nInt.get());
            semZero.release();
        }
        //throw new InterruptedException("even enough");
    }

    public void odd() throws InterruptedException {
        while(nInt.get() < n){
            semOdd.acquire();
            System.out.print(nInt.get());
            semZero.release();
        }
        //throw new InterruptedException("odd enough");
    }

    public static void main(String[] args) throws InterruptedException {

        ZeroEvenOdd test = new ZeroEvenOdd(7);
        Thread[] threads = new Thread[3];

        threads[0] = new Thread(() -> {

                try {
                   test.zero();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            });
        threads[1] = new Thread(() -> {
            try {
                test.odd();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        threads[2] = new Thread(() -> {

            try {
                test.even();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });


        for(int i = 0; i<3; ++i) {
            threads[i].start();
            threads[i].join(10);
        }
    }


   /* @Override
    public void run() {

            if (Thread.currentThread().getName().equals("zero")) {
                try {
                    zero();

                } catch (InterruptedException e) {
                   System.err.println(e);
                }
            } else if (Thread.currentThread().getName().equals("hero")) {
                try {
                    even();

                } catch (InterruptedException e) {
                    System.err.println(e);
                }
            } else {
                try {
                    odd();
                } catch (InterruptedException e) {
                    System.err.println(e);
                }
            }

    }*/
}
