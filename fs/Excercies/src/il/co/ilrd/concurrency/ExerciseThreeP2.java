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
        count_g = 5;
        while(count_g > 0) {
            synchronized(this) {
                    for (int i = 0; i < 5; ++i) {
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
        while(semCount_g < 3) {
            synchronized(this) {
                int msg = 5;
                for (int i = 0; i < msg; ++i) {
                    list.add(i);
                }
                System.out.println("produced!" + java.time.LocalDateTime.now());
                ++semCount_g;
                sem.release(msg);
            }
        }
    }

    public void semaphoreConsume() throws InterruptedException {
        semCount_g = 0;
        while(semCount_g < 3) {
            synchronized(this) {
                    sem.acquire(1);
                    System.out.print("consumed message #" + list.remove(0) + " ");
                    System.out.println(" thread id " + Thread.currentThread().getId() +" " + java.time.LocalDateTime.now());

                ++semCount_g;
            }
        }
    }


    public static void main(String[] args) {
        ExerciseThreeP2 bla = new ExerciseThreeP2();
        Thread[] producers = new Thread[5];
        Thread[] consumers = new Thread[5];

        for (int i = 0; i < 5; ++i) {
            //bla.produce();
            producers[i] = new Thread(bla::semaphoreProduce);
        }
        for (int i = 0; i < 5; ++i) {
            consumers[i] = new Thread(() -> {
                //bla.consume();
                try {

                    bla.semaphoreConsume();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            });
        }

        for (int i = 0; i < 5; ++i) {
            producers[i].start();
            consumers[i].start();
        }
    }

}
