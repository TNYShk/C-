package il.co.ilrd.dsexam;

import java.util.EmptyStackException;
import java.util.Stack;

public class Question6 {
    public Stack<Integer> dataStack = new Stack<>();
    private Stack<Integer> minStack = new Stack<>();

    public void pushData(int data){
        if(minStack.isEmpty())
            minStack.push(data);
        else {
            if (minStack.peek() > data) {
                minStack.push(data);
            } else if (minStack.peek() <= data) {
                minStack.push(minStack.peek());
            }
        }
        dataStack.push(data);
    }

    public int popData(){

        if(dataStack.isEmpty())
            throw new RuntimeException("EMPTY nothing to POP");
        minStack.pop();
        return dataStack.pop();
    }

    public Integer getMinElement(){
        return(minStack.isEmpty())? null: minStack.peek();


    }

    public static void main(String[] args){
        Question6 test = new Question6();

        test.pushData(5);
        test.pushData(30);
        test.pushData(2);
        test.pushData(60);
        System.out.println("elements in data stack: " + test.dataStack.size());
        System.out.println("min value in stack: " + test.getMinElement());
        System.out.println("pop dataStack "+test.popData());
        System.out.println("elements in data stack: " + test.dataStack.size());
        System.out.println("min value in stack: " + test.getMinElement());
        System.out.println("pop dataStack "+test.popData());
        System.out.println("min value in stack: " + test.getMinElement());
        System.out.println("pop dataStack "+test.popData());
        System.out.println("min value in stack: " + test.getMinElement());
        System.out.println("pop dataStack "+test.popData());
        System.out.println("min value in stack: " + test.getMinElement());
        //System.out.println("pop dataStack "+test.popData());
        //System.out.println("min value in stack: " + test.getMinElement());


    }

}
