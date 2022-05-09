package il.co.ilrd.dsexam;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;


public class Question9 {

    private static Object[] converter;
   private static void listToArray(List<Integer> list){
       converter = list.toArray();
   }

   public static void pivotList(List<Integer> list, int pivot){
       listToArray(list);
    LinkedList<Integer> temp = new LinkedList<>();

    for(int i =0; i<converter.length; ++i){
        if ((Integer)converter[i] < pivot){
            temp.addFirst((Integer)converter[i]);
        }
        else{
            temp.addLast((Integer)converter[i]);
        }
    }

       System.out.println(temp);

       }

       public static void main(String[] args){
        LinkedList<Integer> test = new LinkedList<>();
        test.add(1);
        test.add(8);
        test.add(13);
        test.add(3);
        test.add(5);
        test.add(8);
        test.add(6);
        test.add(2);
        test.add(5);
        System.out.println(test);
       Question9.pivotList(test,6);

       }
   }








