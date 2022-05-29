package il.co.ilrd.quiz11_12_syncproblem;

public class MyObject {
    public synchronized void foo(String name){
        try{
            System.out.println("thread " + name+".foo(): started  ");
            Thread.sleep(3000);
            System.out.println("thread " + name+".foo(): ended  " );
        }catch (InterruptedException exc){
            System.out.println("thread " + name+" interrupted  ");
        }
    }

    public static synchronized void barf(String name) throws InterruptedException {
        System.out.println("thread " + name+" static barf(): started ");
        Thread.sleep(3000);
        System.out.println("thread " + name+" static barf(): ended  " );
    }
}
