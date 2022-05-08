package il.co.ilrd.dsexam;

import java.util.Arrays;

public class Question2 {



    public static int[] sumOfTwo(int[] arr, int target){
        Arrays.sort(arr);
        int start = 0;
        int end= arr.length -1;
        int[] answer = {-1,-1};
        while(start< end) {
            int localSum = arr[start] + arr[end];
            if(localSum < target)
                ++start;
            if(localSum > target)
                --end;
            if(localSum == target){
                answer[0] = start;
                answer[1] = end;
                break;
            }
        }
        return answer;
    }

    public static void main(String[] args){
        int[] array = {1,5,8,11};
        int []result = sumOfTwo(array,70);
        System.out.println(result[0] + " " + result[1]);
    }
}
