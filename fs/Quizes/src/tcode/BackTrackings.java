package tcode;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class BackTrackings {
/*
Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.
 */
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> list = new ArrayList<>();
        Arrays.sort(nums);
        backtrack(list, new ArrayList<>(), nums, 0);
        return list;
    }

    private void backtrack(List<List<Integer>> list , List<Integer> tempList, int [] nums, int start){
        list.add(new ArrayList<>(tempList));
        for(int i = start; i < nums.length; i++){
            tempList.add(nums[i]);
            backtrack(list, tempList, nums, i + 1);
            tempList.remove(tempList.size() - 1);
        }
    }

    //from the book, power set O(n 2^n)

    public List<List<Integer>> getSubsets(List<Integer>set, int idx){
        List<List<Integer>> allSubsets;
        if(set.size() == idx){ //base case - an empty set
            allSubsets = new ArrayList<>();
            allSubsets.add(new ArrayList<>());
        }else{
            allSubsets = getSubsets(set,idx+1);
            int item = set.get(idx);
            List<List<Integer>> moresubsets = new ArrayList<>();
            for(List<Integer> subset: allSubsets){
                ArrayList<Integer> newsubset = new ArrayList<>();
                newsubset.addAll(subset);
                newsubset.add(item);
                moresubsets.add(newsubset);
            }
            allSubsets.addAll(moresubsets);
        }
        return allSubsets;
    }

    /*
    Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
    The solution set must not contain duplicate subsets. Return the solution in any order.
     */
    public List<List<Integer>> subsetsWithDup(int[] nums) {
        List<List<Integer>> list = new ArrayList<>();
        Arrays.sort(nums);
        backtrack(list, new ArrayList<>(), nums, 0);
        return list;
    }

    //Permutations
/*
    Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
 */
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> list = new ArrayList<>();
        // Arrays.sort(nums); // not necessary
        backtrack(list, new ArrayList<>(), nums);
        return list;
    }

    private void backtrack(List<List<Integer>> list, List<Integer> tempList, int [] nums){
        if(tempList.size() == nums.length){
            list.add(new ArrayList<>(tempList));
        } else{
            for(int i = 0; i < nums.length; i++){
                if(tempList.contains(nums[i])) continue; // element already exists, skip
                tempList.add(nums[i]);
                backtrack(list, tempList, nums);
                tempList.remove(tempList.size() - 1);
            }
        }
    }
/*
    Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.
 */
public List<List<Integer>> permuteUnique(int[] nums) {
    List<List<Integer>> list = new ArrayList<>();
    Arrays.sort(nums);
    backtrack(list, new ArrayList<>(), nums, new boolean[nums.length]);
    return list;
}

    private void backtrack(List<List<Integer>> list, List<Integer> tempList, int [] nums, boolean [] used){
        if(tempList.size() == nums.length){
            list.add(new ArrayList<>(tempList));
        } else{
            for(int i = 0; i < nums.length; i++){
                if(used[i] || i > 0 && nums[i] == nums[i-1] && !used[i - 1]) continue;
                used[i] = true;
                tempList.add(nums[i]);
                backtrack(list, tempList, nums, used);
                used[i] = false;
                tempList.remove(tempList.size() - 1);
            }
        }
    }

    /*
        given a sorted array (can have duplicates) find the magic number, where int array[magic] = magic. otherwise return -1
     */
    public int magicFast(int[] arr){
        return magicFast(arr,0,arr.length-1);
    }
    private int magicFast(int[]arr,int start,int end){
        if(end<start) return -1;

        int midIdx = (start +end) /2;
        int midVal = arr[midIdx];
        if(midVal == midIdx)
            return midIdx;

        //search left side, up the smaller value idx
        int leftIdx = Math.min(midIdx, midVal);
        int left = magicFast(arr,start,leftIdx);
        if(left>= 0) return left;

        //search right
        int rightIdx = Math.max(midIdx+1, midVal);
        int right = magicFast(arr,rightIdx,end);
        return right;
    }


    public static void main(String[] args){
        int[]arr = {-40,-10,-5,3,3,4,7,7,9,12,13};
        BackTrackings test = new BackTrackings();
        System.out.println(test.magicFast(arr));
    }
}
