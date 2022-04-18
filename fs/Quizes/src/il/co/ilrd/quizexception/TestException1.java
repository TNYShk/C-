package il.co.ilrd.quizexception;

import java.io.IOException;

public class TestException1 {
    public void start() throws IOException{
        throw new IOException();
    }
    public void foo() throws NullPointerException{
        System.out.println("foo in test1");

    }

    public static void main(String[] args){
    TestException2 please = new TestException2();
    try{
        please.start();
    }catch (Exception e){
        e.printStackTrace();
        please.foo();
    }

    }


}
class TestException2 extends TestException1{
    @Override
    public void start(){
        TestException1 trying = new TestException1();
        try {

            trying.start();
            super.start();
        }catch (IOException e){
            System.err.println("here");
            e.printStackTrace();
            trying.foo();
        }

    }

    public void foo() throws RuntimeException{ System.out.println("foo in test2");}

}
