package tcode;

import org.junit.Assert;


import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

public class MajorityElement {
    public int majorityElement(int[] nums) {
        HashMap<Integer,Integer> majorMap = new HashMap<>();
        for(int i: nums){
            majorMap.merge(i,1,Integer::sum);
        }
        Integer max = Collections.max(majorMap.values());
        for (Map.Entry<Integer, Integer> entry : majorMap.entrySet()) {
            if (entry.getValue().equals(max))
                return entry.getKey();
        }
        return max;
    }

    public int difMajotElement(int[] nums){
        Arrays.sort(nums);
        return nums[nums.length/2];
    }

    public static void main(String[] args){
        int[]nums = {3,2,3};
        int[]num = {2,2,1,1,1,2,2};
        int[]numss = {3,3,4};
        int[]numsss = {1,1,1,1,2,3,4};
        MajorityElement test = new MajorityElement();
        System.out.println(test.majorityElement(num));
        System.out.println(test.majorityElement(nums));
        System.out.println(test.majorityElement(numss));
        Assert.assertEquals(test.majorityElement(numsss),test.difMajotElement(numsss));
        Assert.assertEquals(test.majorityElement(numss),test.difMajotElement(numss));
        Assert.assertEquals(test.majorityElement(nums),test.difMajotElement(nums));
        Assert.assertEquals(test.majorityElement(num),test.difMajotElement(num));
    }
}
