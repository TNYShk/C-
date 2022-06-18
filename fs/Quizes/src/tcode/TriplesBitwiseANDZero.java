package tcode;

import java.util.Arrays;

public class TriplesBitwiseANDZero {
/*
    given an int array, return the amount of AND triplets(i,j,k) that are equal to zero
    nums[i]&nums[j]&nums[k] ==0;
    0<=i,j,k <nums.length
 */
    public int countTriplets(int[]nums){
        Arrays.sort(nums);
        if(Arrays.stream(nums).sum()==0){
            return (int) Math.pow(3,nums.length);
        }
        int[] dp = new int[1<<16];

        for(int a: nums)
            dp[a]++;

        for(int i =0; i<2 ; ++i){
            int[] next = new int[dp.length];
            for(int a: nums)
                for(int j=0;j<dp.length;++j)
                    next[a&j] +=dp[j];
            dp = next;
        }
        return dp[0];

    }

    public static void main(String[] args){
        int nums[] = {2,1,3};
        TriplesBitwiseANDZero test = new TriplesBitwiseANDZero();
        System.out.println(test.countTriplets(nums));
        int []nums2 = {0,0,0};
        System.out.println(test.countTriplets(nums2));
    }
}
