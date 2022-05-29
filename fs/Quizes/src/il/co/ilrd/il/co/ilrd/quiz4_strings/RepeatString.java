package il.co.ilrd.quiz4_strings;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class RepeatString {
    public static char[]charArr;
    public static List<List<Integer>> finalList;

    private static void printReverse(String str){
        charArr = str.toCharArray();
        for (int i=str.length()-1; i>=0;--i){
            System.out.print(charArr[i]);
        }
        System.out.println();
    }
    private static String Reverse(String str){
        charArr = str.toCharArray();
        StringBuilder answer = new StringBuilder();
        for (int i=str.length()-1; i>=0;--i){
            answer.append(charArr[i]);
        }
        return String.valueOf(answer);
    }

    private static boolean isPalindrome(String str){
        String rev = Reverse(str);
        return rev.equals(str);
    }

    private static List<List<Integer>> permuate(int[]nums){
        finalList = new LinkedList<>();

            RecPermutate(nums,0,nums.length-1);
            return finalList;
        //System.out.println(local);



    }

    private static void RecPermutate(int[] nums, int start, int end){
        List<Integer> row = new ArrayList<>();
        if(start == end){
            for(int i: nums){
               row.add(i);
            }
            //System.out.print(row);
                finalList.add(row);
            return;
        }
        for(int j = start; j<= end; ++j){
            nums = swap(nums,start,j);
            RecPermutate(nums,start+1,end);
            nums = swap(nums,start,j);
        }

    }



    private static void printPermutations(String str){
       char[]char_arr = str.toCharArray();
       RecPermPrint(char_arr,0,str.length()-1);
    }
    private static void RecPermPrint(char[]arr, int start,int end){
        if(start == end){
            System.out.println(arr);
            return;
        }
        for(int i =start; i<=end; ++i){
            arr = swap(arr,start,i);
            RecPermPrint(arr,start+1,end);
            arr = swap(arr,start,i);
        }
    }

    private static char[] swap(char[]arr,int start, int end){
        char temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        return arr;
    }

    private static int[] swap(int[]arr,int start, int end){
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        return arr;
    }

    public static void main(String[] args){
       /* RepeatString.printReverse("wanna go home");
        String brr =  RepeatString.Reverse("wanna go home");
        System.out.println(brr);
        System.out.println(isPalindrome("123321"));
        System.out.println(isPalindrome("153321"));
        System.out.println(isPalindrome("palo olap"));*/
       // printPermutations("lab");
        int[]ttt = {1,2,3};
        System.out.println(permuate(ttt));
    }
}
