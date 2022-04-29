package il.co.ilrd.exam;

import java.util.HashMap;
/*
    implement the following operations:
    Addition (using lambda expression)
    subtraction (using anonymous class)
    multiplication (using inner class)
    division (using local class)
 */
public class Q36 {
    HashMap<String,Operator> mapOperator = new HashMap<>();

    Operator add = ((a,b) -> a+b);
    Operator minus = new Operator() {
        @Override
        public int operate(int a, int b) {
           return a-b;
        }
    };
    protected class Multiply implements Operator{

        @Override
        public int operate(int a, int b) {
            return a*b;
        }
    }

        public Operator Division(){
            class local implements Operator{

                @Override
                public int operate(int a, int b) {
                    if(b ==0)
                        throw new ArithmeticException();
                    return a/b;
                }
            }
        return new local();
    }
    public Q36(){
        addOperator("addition",add);
        addOperator("subtract",minus);
        addOperator("multiply",new Multiply());
        addOperator("divide", Division());

    }
    interface Operator{
        int operate(int a, int b);
    }
    public void addOperator(String key,Operator o){
        mapOperator.put(key,o);
    }
    public int operate(String key,int a, int b){
        return mapOperator.get(key).operate(a,b);
    }

    public static void main(String[] args){
        Q36 calc = new Q36();
        int sum = calc.operate("addition",3,4);
        int sub = calc.operate("subtract",4,3);
        int mul = calc.operate("multiply",4,3);
        int div = calc.operate("divide",8,2);
        System.out.println("answers are:\n" + sum + " " + sub + " " + mul + " " + div);
    }
}
