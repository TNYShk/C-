package tcode;

import java.util.Stack;

public class Prep<T> {
    Node<T> head;
    Stack<Integer> inbox = new Stack<>();
    Stack<Integer> outbox = new Stack<>();

    private void initStack(){
       for(int i=1;i<6;++i){
           inbox.push(i);
       }
    }
    // find substring inside String
    public static boolean findSubString(String str, String sub){
        System.out.println("idx of sub is: "+str.indexOf(sub));
        return str.contains(sub);
    }

    static class Node<T>{
        T value;
        Node next;

        public Node(T t){
            value= t;
            next = null;
        }
    }
    public void printlist(){
       Node runner = head;
       while (runner != null){
           System.out.print(runner.value+" ");
           runner = runner.next;
       }
       System.out.println();
    }
    //find if there;s a loop in a sll
    public boolean isLoop(){
        Node fast = head;
        Node slow = head;
        int counter = 0;
        while(fast!= null && fast.next != null){
            fast = fast.next.next;
            slow = slow.next;
            ++counter;
            if(fast == slow){
                System.out.println("inner loop size is: "+counter);
                return true;
            }
        }
        return false;
    }
//find and remove loop
    public boolean isLoopRemove(){
        Node fast = head;
        Node slow = head;
        int counter = 0;
        while(fast!= null && fast.next != null){
            fast = fast.next.next;
            slow = slow.next;
            ++counter;
            if(fast == slow){
                removeLoop(counter);
                System.out.println("inner loop size is: "+counter);
                return true;
            }
        }
        return false;
    }
    private void removeLoop(int counter){
        Node runner = head;
        while(--counter>0){
            runner = runner.next;
        }
        runner.next = null;
    }

    //FIFO to LIFP with two stacks

    public int LIFOtoFIFO(){
        initStack();
        while(!inbox.isEmpty()){
            outbox.push(inbox.pop());
        }
        Integer peeky = outbox.pop();
        while(!outbox.isEmpty()){
            inbox.push(outbox.pop());
        }
        return peeky;
    }

    /*
    how to avoid inheritance? (keywords):
        using private, final

    what is polymorphism?
        having many forms, occurs when classed are related by inheritance. allows performing single action in different ways
     */

    public static boolean isStringNumberPalindrome(String number){
        StringBuilder reverse = new StringBuilder(number);
        reverse.reverse();
        return reverse.toString().equals(number);
    }

    public static void main(String[] args){
          System.out.println(findSubString("qwertyuiopa sdfghjklz xcvbnm", "opa"));
          Prep test = new Prep();
          test.head = new Node<String>("hi");
          Node second = new Node<>("why");
          Node third = new Node<>("die");
          Node fourth = new Node<>("cold");
          test.head.next = second;
          second.next = third;
          third.next = fourth;
          fourth.next = second;
          System.out.println(test.isLoopRemove());
          test.printlist();
          System.out.println("\nLIFOtoFIFO test: ");
          System.out.println(test.LIFOtoFIFO());
        System.out.println(test.LIFOtoFIFO());
        System.out.println("is 1?: " +isStringNumberPalindrome("1"));
        System.out.println("is 2222?: " +isStringNumberPalindrome("2222"));
        System.out.println("is 12321?: " +isStringNumberPalindrome("12321"));
        System.out.println("is 112321?: " +isStringNumberPalindrome("112321"));

    }




}
