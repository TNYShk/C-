package tcode;

import java.util.Arrays;

public class FirstMissingPositive {

    public static int firstMissing(int[] nums){
        Arrays.sort(nums);

        int latestVal = 0;

        for(int i = 0; i<nums.length ;++i){
            if(nums[i] > 0){
                if(nums[i] == latestVal+1 || nums[i]== latestVal)
                    latestVal = nums[i];
                else{
                    break;
                }
            }
        }
        return latestVal+1;
    }

    public static void main(String[] args){

        int[]in = {1,2,0};
        int[]inp = {3,4,-1,1};
        int[]inpu = {7,8,9,11,12};
        System.out.println(firstMissing(in));
        System.out.println(firstMissing(inp));
        System.out.println(firstMissing(inpu));
    }
}
