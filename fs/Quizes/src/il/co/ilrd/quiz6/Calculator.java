package il.co.ilrd.quiz6;

public class Calculator implements Person, Male {
    private Operator calculator;

    Operator add = ((a, b) -> a+b);
    Operator minus = new Operator(){
        @Override
        public int operate(int a, int b){
            return a-b;
        }

    };
    private class Multiply implements Operator{

        @Override
        public int operate(int a, int b) {
            return a*b;
        }
    }

    public static int Division(int a, int b){

        class local implements Operator{

           // local(){}

            @Override
            public int operate(int a, int b) {
                return a/b;
            }
        }

        local tries = new local();
        return tries.operate(a,b);
    }


    interface Operator{
        int operate(int a, int b);
    }


    public static void main(String []args){
        Calculator sam = new Calculator();
        sam.sayHello();

        Male.sayHello();
        System.out.println(sam.add.operate(10,4));
        System.out.println(sam.minus.operate(10,4));
        Multiply div = sam.new Multiply();
        System.out.println(div.operate(4,5));
        System.out.println(sam.Division(12,4));
    }




}
interface Person{
    default void sayHello(){
        System.out.println("helloP");
    }
}
interface Male{
    static void sayHello(){
        System.out.println("Hi");
    }
}