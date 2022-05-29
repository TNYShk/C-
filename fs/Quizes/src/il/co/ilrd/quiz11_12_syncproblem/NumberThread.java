package il.co.ilrd.quiz11_12_syncproblem;

public class NumberThread extends FizzBuzzThread{

    public NumberThread(boolean div3, boolean div5, int max) {
        super(div3, div5, max, null);
    }
    public void print(){
        System.out.print(current +" ");
    }

    public static void main(String[] args){
        Thread[] threads = {    new FizzBuzzThread(true,true,16,"FizzBuzz"),
                new FizzBuzzThread(true,false,16,"Fizz"),
                new FizzBuzzThread(false,true,16,"Buzz"),
                new NumberThread(false,false,16)};
        for(Thread i: threads){
            i.start();
        }
    }
}
