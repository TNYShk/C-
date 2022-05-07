package il.co.ilrd.cake;

import java.util.List;
import java.util.Stack;

public class StackNode {
    private Node head;
    private Stack<Node> stacky;

    public StackNode(){
        stacky = new Stack<>();
    }

    private class Node{
        private Object data;
        private Node next;

        public Node(Object d){
            this.data = d;
            next = null;
        }
    }

    public void addData(Object data){
        if(head == null){
            head = new Node(data);
            stacky.add(head);
        }else{
            Node runner = head;
            while(runner.next != null){

                runner = runner.next;
            }
            runner.next = new Node(data);
            stacky.add(runner.next);
        }
    }

    public String toString(){
        Node runner = head;
        String list = "SLL:\n{ " ;
        while(runner != null){
            list +=runner.data + " ";
            runner = runner.next;
        }
        list +="}";
        return list;
    }

    public void printStack(){
        System.out.println("stack content:");
        System.out.print("[");
        while(!stacky.isEmpty()){
            System.out.print(stacky.pop().data + " ");
        }
        System.out.print("]");
        System.out.println();
    }

    public void intoStackReverse(){
        Node runner = head;
        Stack<Node> stack = new Stack<>();
        while(runner.next != null){

            stack.add(runner);
            runner = runner.next;
        }
        head = runner;
        while(!stack.isEmpty()){
            runner.next = stack.pop();
            runner= runner.next;
        }
        runner.next = null;
    }

    public void reverseList(){
        Node prev = null;
        Node runner = head;
        Node next;

        while(runner!= null){
            next = runner.next;
            runner.next = prev;
            prev = runner;
            runner = next;
        }
            head = prev;
    }

    public void sortStack(){
        Stack<Node> sorted = new Stack<>();
       while(!stacky.isEmpty()){
           Node peeky = stacky.pop();

           while(!sorted.isEmpty()  && ((int)peeky.data)> ((int)sorted.peek().data)){
               stacky.push(sorted.pop());
           }
          sorted.push(peeky);
       }
       stacky = sorted;
    }

    public void RecSortStack(){
        if(stacky.isEmpty())
            return;
        Node peeky = stacky.pop();
        RecSortStack();
        isSorted(peeky);
    }
    private void isSorted(Node peeky){
        if(!stacky.isEmpty() && (((int)peeky.data)> ((int)stacky.peek().data))){
            Node temp = stacky.pop();
            isSorted(peeky);
            stacky.push(temp);
            return;
        }
        stacky.push(peeky);
    }

    public static void main(String[] args){
        StackNode test = new StackNode();
        StackNode reserve = new StackNode();
        test.addData(1);
        test.addData(12);
        test.addData(6);
        test.addData(5);
        test.addData(30);
        reserve.addData(0);
        reserve.addData(-5);
        reserve.addData(900);
        reserve.addData(15);
        reserve.addData(30);

        System.out.println(test);

        test.intoStackReverse();
        System.out.println(test);
        test.reverseList();
        System.out.println(test);


        reserve.RecSortStack();
        reserve.printStack();
        System.out.println();
        test.sortStack();
        test.printStack();

    }
}
