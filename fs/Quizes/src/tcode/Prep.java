package tcode;

import java.util.*;

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

//using "min heap" via priorityQ
    public static <T>Node<T> mergeKSortedLists(Node[] lists){
        PriorityQueue<Node> pq = new PriorityQueue<>(Comparator.comparingInt(a -> (int) ( a).value));

        pq.addAll(Arrays.asList(lists).subList(0, lists.length));

        Node start = null,end = null;

        while(!pq.isEmpty()){
            Node min = pq.poll();

            if(start == null){
                start = end = min;
            }
            else{
                end.next = min;
                end = min;
            }
            if(min.next != null)
                pq.add(min.next);
        }
        return start;
    }

    //merge K lists via merge sort, merging 2 lists each time
    public static <T> Node<T> sortedListsMerge(Node<T> a, Node<T>b){
        if(a == null)
            return b;
        else if(b == null)
            return a;

        Node<Integer> result;
        if((Integer)a.value <=  (Integer) b.value){
            result = (Node<Integer>) a;
            result.next = sortedListsMerge(a.next, b);
        }
        else{
            result = (Node)b;
            result.next = sortedListsMerge(a, b.next);
        }
        return (Node<T>) result;
    }

    public static <T> Node<T> mergeKLists(Node[] lists){
        if (lists == null || lists.length == 0)
            return null;

        int last = lists.length -1;

        while(last != 0){
            int i = 0, j = last;
            while(i < j){
                lists[i] = sortedListsMerge(lists[i], lists[j]);

               i++;
               j--;
                if(i >= j)
                    last = j;
            }
        }
    return lists[0];
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

    public static void wordCompress(String s){
        LinkedHashMap<Character,Integer> compressor = new LinkedHashMap<>();
        for (int i=0;i<s.length();++i){
            compressor.merge(s.charAt(i),1,Integer::sum);
        }
        System.out.println("compressed: "+compressor);
        wordDecompress(compressor);
    }

    public static void wordDecompress(LinkedHashMap<Character,Integer> map){
        StringBuilder result = new StringBuilder();
        for(Map.Entry<Character,Integer> entry: map.entrySet()){
            int letterCount = entry.getValue();
            while(letterCount-- > 0){
                result.append(entry.getKey());
            }
        }
        System.out.println("decompressed: "+ result);
    }

/*    find repetitive char in a char arr */
    //lut
    public static char findRepeatChar(String str){
        char[]arr = str.toCharArray();
        boolean[]unique = new boolean[128];
        for(int i=0;i<arr.length;++i){
            if(unique[arr[i]])
                return arr[i];
            unique[arr[i]] = true;
        }
        return ' ';
    }
    //bitwise
    public static char findRepeatCharBit(String str) {
        int checkAgainst = 0;
        for (int i = 0; i < str.length(); ++i) {
            int tmp = Character.getNumericValue(str.charAt(i) - 10);
            if ((checkAgainst & (1 << tmp)) > 0) {
                System.out.println("duplicate: " + str.charAt(i));
                return str.charAt(i);
            }
            checkAgainst |= (1 << tmp);

        }
        return ' ';
    }
    //hash
    public static char findRepeatCharsHash(String str){
        Set<Character> unqMap = new HashSet<>();
        for(int i = 0;i<str.length();++i){
            if(unqMap.contains(str.charAt(i))){
                return str.charAt(i);
            }
            unqMap.add(str.charAt(i));
        }
        return ' ';
    }
    public static int JosephusLastManStand(int soldiersNum){
        int[]soldiers = new int[soldiersNum];
        initCircle(soldiers);
        int idx = 0;
        int nextToDie = 0;
        while(idx != soldiers[idx]){
            nextToDie = soldiers[soldiers[idx]];
            soldiers[soldiers[idx]] = 0;
            soldiers[idx] = nextToDie;
            idx = nextToDie;
        }
        System.out.println("last man standing is soldier num "+ (idx+1));
        return idx;
    }

    public static void initCircle(int[]arr){
        for(int i=0;i<arr.length;++i){
            arr[i] = (i+1)%arr.length;
        }
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
        wordCompress("HARRY");
        wordCompress("ccccOddEEE");

        Node<Integer>[] lists = new Node[3];
        lists[0] = new Node<>(1);
        lists[0].next = new Node(5);
        lists[0].next.next = new Node(7);

        lists[1] = new Node<>(2);
        lists[1].next = new Node(3);
        lists[1].next.next = new Node(6);
        lists[1].next.next.next = new Node(9);

        lists[2] = new Node<>(4);
        lists[2].next = new Node(8);
        lists[2].next.next = new Node(10);

        //test.head = mergeKSortedLists(lists);
        test.head = mergeKLists(lists);
        test.printlist();

        String str = "Tatyamma";
        System.out.println(findRepeatChar(str));
        System.out.println(findRepeatCharBit(str));
        System.out.println(findRepeatCharsHash(str));
        System.out.println(12<<1);
        System.out.println(Integer.toBinaryString(1<<5));

        System.out.println("idx of last man standing is: "+   JosephusLastManStand(6));



    }




}
