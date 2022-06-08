package leetcode;

import java.util.*;

public class ArrayString {
    public static List<List<Integer>> threeSum(int[] num) {
        Arrays.sort(num);
        List<List<Integer>> res = new LinkedList<>();
        for (int i = 0; i < num.length-2; i++) {
            if (i == 0 || (i > 0 && num[i] != num[i-1])) {
                int lo = i+1, hi = num.length-1, sum = 0 - num[i];
                while (lo < hi) {
                    if (num[lo] + num[hi] == sum) {
                        res.add(Arrays.asList(i,lo,hi));
                        //res.add(Arrays.asList(num[i], num[lo], num[hi]));
                        while (lo < hi && num[lo] == num[lo+1]) lo++;
                        while (lo < hi && num[hi] == num[hi-1]) hi--;
                        lo++; hi--;
                    } else if (num[lo] + num[hi] < sum) lo++;
                    else hi--;
                }
            }
        }
        return res;
    }
    public static List<List<Integer>> threeSumZero(int[] nums) {
        Set<List<Integer>> allOptions = new HashSet<>();

        Arrays.sort(nums);
        if(nums[0]>0)
            return null;

        for(int i = 0; i<nums.length; ++i){
            int localSum = 0-nums[i];
            nums = swapPlaces(nums,i);
            int[] option = sumToTarget(nums,localSum);
            if(option != null)
                allOptions.add(convert(option,i));
        }

       for(List list: allOptions){
           System.out.println(list);
       }
            return new ArrayList<>(allOptions);
    }
    private static int[] swapPlaces(int[] nums, int where){
        int holder = nums[0];
        nums[0] = nums[where];
        nums[where] = holder;
        return nums;

    }

    private static List<Integer> convert(int[] arr, int idx){
        List<Integer> converted = new LinkedList<>();
        converted.add(idx);
        for(int i: arr){
            if(i != idx)
            converted.add(i);
        }
        return converted;
    }

  public static int[] sumToTarget(int[]arr, int target){
        Arrays.sort(arr);
        int start = 0;
        int end = arr.length-1;
        while(start < end){
            int localSum = arr[start] + arr[end];
            if(localSum == target){
                int[] ans = {start,end};
                System.out.println("target: "+target+ " idx: "+ start+" , "+end);
                return ans;
            }
            if(localSum<target)
                ++start;
            else{
                --end;
            }
        }
        return null;
    }
    /*
  public static List<int[]> sumToTarget(int[]arr, int target){
      Arrays.sort(arr);
      List<int[]> options = new LinkedList<>();
      int start = 0;
      int end = arr.length-1;
      while(start < end){
          int localSum = arr[start] + arr[end];
          if(localSum<target)
              ++start;
          else if(localSum>target)
              --end;
          else{
              int[] ans = {start,end};
              System.out.println("target: "+target+ " idx: "+ start+" , "+end);
              options.add(ans);
              break;
          }
      }
      return options;
  }
*/


    private static boolean helper(int i, int k, int j){
        return ((i !=k) && (j!=k) &&(i != j));
    }

    public static void main(String[] args){
        int[] num = {-1,0,1,2,-1,-4}; // -4,-1,-1,0,1,2
        int[] another = {0,0,0,0};
        int[] anothers = {0,1,1};
        int[] c = {-2,0,1,2};
        int[] d = {1,2,-2,-1};
        int[] e = {-1,0,1,0};
        //System.out.println(sumToTarget(num,0));
       //threeSumZero(num);
        //threeSumZero(c);
        threeSumZero(num);
        System.out.println(threeSum(num));
        //threeSumZero(another);
        /*System.out.println(threeSum(num));
        System.out.println(threeSum(another));
        System.out.println(threeSum(anothers));
        System.out.println(threeSum(c));
        System.out.println(threeSum(d));
        System.out.println(threeSum(e));*/
    }
}
