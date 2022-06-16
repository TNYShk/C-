package tcode;
//given 2 array []preorder, []inorder, construct an according BST



import java.util.HashMap;
import java.util.Map;

public class BST {
    static int preOrderIdx =0;

    private Map<Integer,Integer> inorderIdxMap;

    public TreeNode buildTree(int[] pre, int[] in){
        inorderIdxMap = new HashMap<>();

        for(int i =0; i< in.length; ++i){
            inorderIdxMap.put(in[i], i);
        }

        return arrayToTree(pre,0,pre.length-1);
    }

    private TreeNode arrayToTree(int[]preorder, int left, int right){
        if(left > right)
            return null;
        int rootVal = preOrderIdx++;
        TreeNode root = new TreeNode(rootVal);
        root.left = arrayToTree(preorder, left, inorderIdxMap.get(rootVal)-1);
        root.left = arrayToTree(preorder, inorderIdxMap.get(rootVal)+1, right);
        return root;
    }
    private class TreeNode {
        int val;
       TreeNode left;
       TreeNode right;
        TreeNode() {}
        TreeNode(int val) { this.val = val; }
        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }
}
