package il.co.ilrd.quiz10;

import java.io.IOException;
import java.util.concurrent.TimeUnit;

public class MyWaitNotify {
    String myMonitorObj = "";
    volatile boolean wasSignalled = false;

    public void doWait(){
        synchronized (myMonitorObj){
            while(!wasSignalled){
                try{
                    System.out.println("in doWait: "+Thread.currentThread().getName());
                    myMonitorObj.wait();
                }catch(InterruptedException e){
                    e.printStackTrace();
                }
            }

            wasSignalled = false;
        }
    }

    public void doNotify(){
        synchronized (myMonitorObj){
            System.out.println("in doNotify "+Thread.currentThread().getName());
            wasSignalled = true;
            myMonitorObj.notify();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        MyWaitNotify test = new MyWaitNotify();

        Thread run = new Thread(() ->{

            test.doWait();
            //test.doNotify();
        });
        run.start();
       // System.out.println(Thread.currentThread().getName());
        //TimeUnit.SECONDS.sleep(10);
        Thread runner = new Thread(() ->{
            test.doNotify();
        });
        runner.start();
        //System.out.println(Thread.currentThread().getName());

    }
}
