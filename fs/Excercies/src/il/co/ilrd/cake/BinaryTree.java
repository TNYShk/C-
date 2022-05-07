package il.co.ilrd.cake;

import java.util.Arrays;
import java.util.List;

public class BinaryTree {
    static Node head;




    public Node makeBST(int[] arr, int left, int right){
        if(left >  right)
            return null;

        int middle =  (left+right)/2;
        Node node = new Node(arr[middle]);
        node.left = makeBST(arr, left, middle-1);
        node.right = makeBST(arr, middle+1, right);

        return node;
    }

        public void printTree(Node head){

        if(head == null)
            return;
        System.out.print(head.data + " ");
        printTree(head.left);
        printTree(head.right);
        }

    class Node{
        int data;
        Node left;
        Node right;

        Node(int data){
            this.data = data;
            left = null;
            right = null;
        }
    }
    public static void main(String[] args){
        int[] arr = {4,5,6,7,8,9};
        int[] barr = {2,3,4,5,72};
        BinaryTree test = new BinaryTree();
        int n = arr.length;
        head = test.makeBST(arr,0,n-1);
        test.printTree(head);
        System.out.println();
        int nn = barr.length;
        head = test.makeBST(barr,0,nn-1);
        test.printTree(head);

    }
    /** LEETCODE
     * Definition for a binary tree node.
     * public class TreeNode {
     *     int val;
     *     TreeNode left;
     *     TreeNode right;
     *     TreeNode() {}
     *     TreeNode(int val) { this.val = val; }
     *     TreeNode(int val, TreeNode left, TreeNode right) {
     *         this.val = val;
     *         this.left = left;
     *         this.right = right;
     *     }
     * }

    class Solution {
        public TreeNode sortedArrayToBST(int[] nums) {
            int left = 0;
            int right = nums.length -1;
            return makeBST(nums,left,right);
        }

        private TreeNode makeBST(int[] nums, int left, int right){
            if(left> right)
                return null;

            int middle = (left+right)/2;
            TreeNode root = new TreeNode(nums[middle],makeBST(nums,left, middle -1),makeBST(nums,middle+1, right));

            return root;
        }
    }
     */
}
