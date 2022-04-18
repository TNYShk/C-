package il.co.ilrd.cake;


import org.testng.annotations.Test;

public class JoinTest  extends Thread{

    public void run(){
            try{
                Thread.sleep(1000);
            }catch( Exception e){
                System.err.print(e);
            }
            System.out.println(java.time.LocalDateTime.now() + " " +currentThread().getName() );

    }

/*
    public static void main(String []args){

        try{
            Thread t = new Thread(new Runnable() {
                @Override
                public void run() {
                    throw new RuntimeException();
                }
            });
            t.start();
        } catch(RuntimeException e){
            System.out.println(currentThread().getName()+ "***********");
        }




       JoinTest t1 = new JoinTest();
        JoinTest t2 = new JoinTest();
        JoinTest t3 = new JoinTest();
        t1.start();
        try {
            t1.join(); // calling join() method
        } catch(Exception e) {
            System.err.println(e);
        }
        t2.start();
        t3.start();
         }
*/






}
