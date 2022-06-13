package leetcode;

import java.util.*;

public class SumOfTwo {

    public static List<Set<Integer>> sumOfTwo(int[]arr, int target){
        Arrays.sort(arr);
        //printArr(arr);
        List<Set<Integer>> ans = new LinkedList<>();
        int start = 0;
        int end = arr.length-1;

        while(start<end){
            int localSum = arr[start] + arr[end];
            if(localSum == target){
                Set<Integer> lock = new HashSet<>(arr.length);
                lock.add(start);
                lock.add(end);
                ans.add(lock);
               ++start;
            }
           else if(localSum<target)
                ++start;
           else
                --end;
        }
       return ans.isEmpty()?null:ans;
    }

    private static void printArr(int[] arr){
        for(int i: arr){
            System.out.print(i+" ");
        }
        System.out.println();
    }
    private static void printSet(List<Set<Integer>>fin){
        for(int i =0; i<fin.size();++i){
            System.out.println(fin.get(i));
        }
    }

    public static void sumAlltoZero(int[] arrr){
        List<Set<Integer>>duce = new LinkedList<>();
        for(int i = 0; i<arrr.length;++i) {
            duce = sumOfTwo(arrr, 0 - arrr[i]);
            if (duce != null)
                duce.get(0).add(i);
        }
        printSet(duce);
    }
    public static void main(String[] args){
        int[] arr = {1,45,6,2,5,30,30,25,5,4,15};
        int[] zeros = {-1,0,1};
        int[]moreZ = {-5,0,0,0,1,4};
    List<Set<Integer>>fin = sumOfTwo(arr,10);
    //sumAlltoZero(zeros);
        sumAlltoZero(moreZ);
      //printSet(fin);
    }
}
