package il.co.ilrd.quiz11_12_syncproblem;

public class SyncMethod implements Runnable {
    private String name;
    private MyObject myObj;

    public SyncMethod(MyObject mine, String n){
        name = n;
        myObj = mine;
    }
    @Override
    public void run(){
        myObj.foo(name);
        try {
            myObj.barf(name);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args){
        MyObject mew = new MyObject();
        MyObject bark = new MyObject();
        SyncMethod test = new SyncMethod(mew,"1");
        SyncMethod test2 = new SyncMethod(bark,"2");
        SyncMethod test3 = new SyncMethod(bark,"3");
        Thread ehy = new Thread(test);
        Thread uff = new Thread(test2);
        Thread three = new Thread(() ->{
            test3.run();
        });
        ehy.start();
        uff.start();
       three.start();

    }
}
