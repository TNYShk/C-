package il.co.ilrd.quiz6;

import com.sun.org.apache.xpath.internal.operations.Div;

import java.util.HashMap;

public class Calculator implements Person, Male {
    HashMap<String,Operator> mapOperaotr = new HashMap<>();

    private void addOperator(String key,Operator o){
        mapOperaotr.put(key, o);
    }
    public float operate(String key, float a, float b) {
        return mapOperaotr.get(key).operate(a, b);
    }

    private Calculator(){
        addOperator("add",add);
        addOperator("subtract", minus);
        addOperator("multiply", new Multiply());
        addOperator("divide",Division());
    }

    Operator add = ((a, b) -> a+b);
    Operator minus = new Operator(){
        @Override
        public float operate(float a, float b){
            return a-b;
        }
    };

    private class Multiply implements Operator{

        @Override
        public float operate(float a, float b) {
            return a*b;
        }
    }

    public Operator Division(){

        class local implements Operator{

            @Override
            public float operate(float a, float b) {
                if (0 == b){
                    throw new ArithmeticException();
                }
                return a/b;
            }
        }

        return new local();
    }

    interface Operator{
        float operate(float a, float b);
    }


    public static void main(String []args){
        Calculator sam = new Calculator();

        System.out.println(sam.operate("add", 4,5));
        System.out.println(sam.operate("subtract", 4,5));
        System.out.println(sam.operate("divide", 4,5));
        System.out.println(sam.operate("multiply", 4,5));
        Male.sayHello();
        sam.sayHello();
        System.out.println(sam.add.operate(10,4));
        System.out.println(sam.minus.operate(10,4));
        Multiply div = sam.new Multiply();
        System.out.println(div.operate(4,5));
        System.out.println(sam.Division().operate(5,2));
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