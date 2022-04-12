package il.co.ilrd.concurrency;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Semaphore;


public class ExerciseThreeP2 {
    private List<Number> list = new LinkedList<>();
    private Semaphore sem = new Semaphore(0);
   private int count_g = 0;
    private int semCount_g = 0;

    public void produce() {
        count_g = 10;
        while(count_g > 0) {
            synchronized(this) {
                    for (int i = 0; i < 10; ++i) {
                        list.add( i * i);
                    }
                    System.out.println("production wrap!");
            --count_g;
            }
        }
    }

    public void consume() {
        count_g = 5;
        while(count_g > 0) {
            synchronized(this) {

                    System.out.print("consumed " + list.remove(0) + " ");
                    System.out.println(Thread.currentThread().getName());
            --count_g;
            }
        }
    }

    public void semaphoreProduce() {
        semCount_g = 0;
        while(semCount_g < 1) {
            synchronized(this) {
                for (int i = 0; i < 10; ++i) {
                    list.add(i);
                }
                System.out.println("produced!");
                ++semCount_g;
                sem.release(10);
            }
        }
    }

    public void semaphoreConsume() throws InterruptedException {
        semCount_g = 0;
        while(semCount_g < 2) {
            synchronized(this) {
                sem.acquire(1);
                if (!list.isEmpty()) {
                    System.out.print("consumed message #" + list.remove(0) + " ");
                    System.out.println(" thread id " + Thread.currentThread().getId());
                }
                ++semCount_g;
            }
        }
    }


    public static void main(String[] args) {
        ExerciseThreeP2 bla = new ExerciseThreeP2();
        Thread[] producers = new Thread[3];
        Thread[] consumers = new Thread[3];

        for (int i = 0; i < 3; ++i) {
            producers[i] = new Thread(new Runnable() {
                @Override
                public void run() {
                    //bla.produce();
                    bla.semaphoreProduce();
                }
            });
        }
        for (int i = 0; i < 3; ++i) {
            consumers[i] = new Thread(new Runnable() {
                @Override
                public void run() {
                    //bla.consume();
                    try {

                        bla.semaphoreConsume();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            });
        }

        for (int i = 0; i < 3; ++i) {
            producers[i].start();
            consumers[i].start();
        }
    }

}
