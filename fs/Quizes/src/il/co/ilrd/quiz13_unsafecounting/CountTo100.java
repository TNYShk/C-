package il.co.ilrd.quiz13_unsafecounting;

import java.util.concurrent.atomic.AtomicInteger;

public class CountTo100 implements Runnable{
    private static int cnt = 0;
    private static AtomicInteger cant = new AtomicInteger(0);

    @Override
    public void run() {
        int i = 0;
        int localCnt = 0;
        System.out.println( Thread.currentThread().getName());
        for(i=0; i<100; ++i){
            localCnt = cnt;
            ++localCnt;
            cnt = localCnt;
        }
       for(i=0; i<100; ++i) {
           cant.getAndIncrement();
       }
    }

    public static void main(String[] args){
        Thread first = new Thread(new CountTo100(), "first");
        Thread second = new Thread(new CountTo100(), "second");
        first.start();
        second.start();

        try{

            first.join();
            second.join();
        }catch (InterruptedException e){
            e.printStackTrace();
        }
        System.out.println("The counter is "+ CountTo100.cnt);
        System.out.println("The Atomic counter is "+ CountTo100.cant);
    }
}
