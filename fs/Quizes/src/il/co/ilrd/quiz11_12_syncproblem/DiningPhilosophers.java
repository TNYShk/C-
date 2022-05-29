package il.co.ilrd.quiz11_12_syncproblem;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class DiningPhilosophers extends Thread{
    private int bites = 10;
    private int counter = 0;
    private Chopstick lower, higher;

    public DiningPhilosophers(int i, Chopstick left, Chopstick right){
        counter = i;
        if(left.getNumber() < right.getNumber()){
            this.lower = left;
            this.higher = right;
        }else{
            this.lower = right;
            this.higher =left;
        }
    }

    public void eat(){
        pickUp();
        chew();
       putDown();
    }
    public void pickUp(){
       lower.pickUp();
        higher.pickUp();
    }

    public void putDown(){
        higher.putDown();
        lower.putDown();
    }
    public void run(){
        for(int i = 0; i< bites; ++i){
            eat();
        }
    }
    public void chew(){
        System.out.println(Thread.currentThread().getId() + " is chewing: " + ++counter);
    }

    static class Chopstick {
        private static Lock lock;
        private int number;


        public Chopstick(int n) {
            lock = new ReentrantLock();
            this.number = n;
        }
        public static boolean pickUp(){
            return lock.tryLock();
        }
        public static void putDown(){
            lock.unlock();
        }
        public int getNumber(){
            return number;
        }
    }

    public static void main(String[] args){
        for(int i =0; i<3;++i) {
            DiningPhilosophers test = new DiningPhilosophers(i, new Chopstick(2), new Chopstick(3));
            test.start();
        }


    }
}
