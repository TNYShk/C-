package il.co.ilrd.dsexam;


import java.util.LinkedList;



public class Question9 {

    private Node head;



    public Question9(Node header){
        this.head = header;
    }

    public void pivotList( int pivot){

        LinkedList<Node> list = new LinkedList<>();
        Node<Object> pivo = new Node<>(pivot,null);
        //list.add(pivo);

        Node runner = head;

        while(runner != null){

            if((Integer)runner.data < pivot){
                list.addFirst(new Node(runner.data));
            }else{
                list.addLast(new Node(runner.data));
            }
            runner = runner.next;
        }
        //list.remove(pivo);
       head = list.get(0);
        System.out.println(list + " " + head.toString());
    }




     static class Node<T>  {
        private T data;
        private Node next;

        public Node(T data){
            this.data = data;
            this.next = null;
        }
        public Node(T data, Node<T> next){
                this.data =  data;
                this.next = next;
            }
         @Override
         public String toString(){
             return ( " "+ this.data + " ");
         }
    }


    public static void main(String[] args){

        Node another = new Node(99);
        Node fifth = new Node(5);
        Node four = new Node(700);
        Node third = new Node(9);
        Node second = new Node(7);
        Node first = new Node(4);
        first.next = second;
        second.next = third;
        third.next = four;
        four.next = fifth;
        fifth.next = another;

        Question9 test = new Question9(first);

        while(test.head != null) {
            System.out.print(test);
          test.head = test.head.next;
        }
        System.out.println();
        test.head = first;
       test.pivotList(8);

        while(test.head != null) {
            System.out.print(test.head);
            test.head = test.head.next;
        }
        System.out.println();

    }
}







