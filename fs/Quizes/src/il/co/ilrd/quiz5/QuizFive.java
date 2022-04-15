package il.co.ilrd.quiz5;

public class QuizFive implements SomeInterface {

        public void foo(){
            System.out.println("my new foo!");
        }

        public static void main(String []args){
            QuizFive sc = new QuizFive();
        sc.foo();
    }

}

interface SomeInterface{
    default void foo(){
        System.out.println("my foo");
    }
}

