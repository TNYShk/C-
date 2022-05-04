package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;

public class ZeroEvenOdd {
    private final int n;
    static volatile int inti = 0;
    private final Semaphore semZero = new Semaphore(1);
    private final Semaphore semEven = new Semaphore(0);
    private final Semaphore semOdd = new Semaphore(0);
    static volatile boolean isEven = false;

    public ZeroEvenOdd(int n) {
        this.n = n;
    }

    public void zero() throws InterruptedException {
        for(int i =0; i< n; ++i){
            semZero.acquire();
            System.out.print("0");
           ++inti;

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
        for(int i =2; i<= n; i+=2){
            semEven.acquire();
            System.out.print(inti);
            semZero.release();
        }

    }

    public void odd() throws InterruptedException {
        for(int i =1; i<= n; i+=2) {
            semOdd.acquire();
            System.out.print(inti);
            semZero.release();
        }

    }

    public static void main(String[] args) throws InterruptedException {

        ZeroEvenOdd test = new ZeroEvenOdd(5);
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
            //threads[i].join(10);
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
