package il.co.ilrd.trees;

import java.util.LinkedList;
import java.util.Queue;

import org.junit.Assert;
import org.junit.Test;

public class AVL<K> {
    private Node<K> root;
    class Node<K> {
        K key;
        int height;
        Node<K>[] child;

        {
            child = new Node[2];
        }


        public Node(K key) {
            this.key = key;
            child[0] = null;
            child[1] = null;
        }
    }

    public void insert(K key){
        root = insert(root,key);
    }

    private Node<K> insert(Node<K> node, K key) {
        if (node == null) {
            return new Node(key);
        } else if ((Integer)node.key > (Integer)key) {
            node.child[0] = insert(node.child[0], key);
        } else if ((Integer)node.key < (Integer)key) {
            node.child[1] = insert(node.child[1], key);
        } else {
            throw new RuntimeException("duplicate Key!");
        }
        return rebalance(node);
    }

    public void delete(K key){
        root = delete(root,key);
    }

    private Node<K> delete(Node<K> node, K key){

        if (node == null) {
            return null;
        } else if ((Integer) node.key > (Integer)key) {
            node.child[0] = delete(node.child[0], key);
        } else if ((Integer) node.key < (Integer)key) {
            node.child[1] = delete(node.child[1], key);
        } else {
            if (node.child[0] == null || node.child[1] == null) {
                node = (node.child[0] == null) ? node.child[1] : node.child[0];
            } else {
                Node mostLeftChild = diveLeft(node.child[1]);
                node.key = (K) mostLeftChild.key;
                node.child[1] = delete(node.child[1], node.key);
            }
        }
        if (node != null) {
            node = rebalance(node);
        }
        return node;
    }

    private int whichChild(int num){
        return (num > 0)? 1: 0;
    }

    private int goWhere(boolean side){
        if(side)
            return 0;
        return 1;
    }

    private Node<K> diveLeft(Node<K> node) {
        Node<K> diver = node;
        while(diver.child[0] != null)
            diver = diver.child[0];
        return diver;
    }



    public Node<K> getRoot(){
        return this.root;
    }

    public int getHeight(){
        return(root== null)? 0 : root.height;
    }
    private Node<K> rebalance(Node<K> node){
        updateHeight(node);
        int scale = getBalance(node);
        if(Math.abs(scale) >1){
            if(scale == -2){
                if (0 <= getBalance(node.child[whichChild(scale)])) {
                    node.child[whichChild(scale)] = rotateNode(node.child[whichChild(scale)], 0);
                }
                return rotateNode(node,1);
            }
            else if(scale == 2){
                if (0 >= getBalance(node.child[whichChild(scale)])) {
                    node.child[whichChild(scale)] = rotateNode(node.child[whichChild(scale)], 1);
                }
                return rotateNode(node,0);

            }
        }
        return node;
    }
    private int otherDir(int side){
        return (side == 0)? 1: 0;
    }
    private Node<K> rotateNode(Node<K> node, int direction){
        Node<K> rotator = node.child[otherDir(direction)];

        node.child[otherDir(direction)] = rotator.child[direction];
        rotator.child[direction] = node;

        updateHeight(node);
        updateHeight(rotator);
        return rotator;
    }


    private void updateHeight(Node<K> node){
        node.height = 1+ Math.max(getHeight(node.child[0]),getHeight(node.child[1]));
    }
    public int getBalance(Node<K> node){
        return (node == null)? 0 : getHeight(node.child[1]) - getHeight(node.child[0]);
    }

    private int getHeight(Node<K> node){
        return (node == null)? 0: node.height;
    }

    public Node<K> find(K key){

        Node<K> runner = root;
        while (runner != null) {
            if (runner.key == key) {
                break;
            }
            runner = (Integer) runner.key < (Integer) key ? runner.child[1] : runner.child[0];
        }
        return runner;
    }
    public void printTree(){
        printTree(root,root.height);
    }
    private void printTree(Node node, int height){
        if(node == null)
            return;

        printTree(node.child[0],node.height);
        System.out.print(node.key + " ");
        printTree(node.child[1],node.height);
    }

    public void BFSPrint(Node root){
        Queue<Node> qTree = new LinkedList<>();
        qTree.add(root);

        while(!qTree.isEmpty()){
            Node temp = qTree.poll();
            System.out.print(temp.key + " ");

            if(temp.child[0] != null){
                qTree.add(temp.child[0]);
            }
            if(temp.child[1] != null){
                qTree.add(temp.child[1]);
            }

        }
    }

    public static void main(String[] args){

    }
    @Test
    public void givenEmptyTree_whenHeightCalled_shouldReturnMinus1() {
        AVL tree = new AVL();
        Assert.assertEquals(0, tree.getHeight());
    }

    @Test
    public void givenEmptyTree_whenInsertCalled_heightShouldBeZero() {
        AVL tree = new AVL();
        tree.insert(1);
        tree.insert(2);
        tree.insert(3);

        Assert.assertEquals(2, tree.getHeight());
    }

    @Test
    public void givenEmptyTree_whenInsertCalled_treeShouldBeAvl() {
        AVL tree = new AVL();
        tree.insert(1);
        Assert.assertTrue(isAVL(tree));
    }

    @Test
    public void givenSampleTree_whenInsertCalled_treeShouldBeAvl() {
        AVL tree = getSampleAVLTree();
        int newKey = 11;
        tree.insert(newKey);
        Assert.assertTrue(isAVL(tree));
    }

    @Test
    public void givenSampleTree_whenFindExistingKeyCalled_shouldReturnMatchedNode() {
        AVL tree = getSampleAVLTree();
        int existingKey = 2;
        AVL.Node result = tree.find(existingKey);
        Assert.assertEquals(result.key, existingKey);
    }

    @Test
    public void givenSampleTree_whenFindNotExistingKeyCalled_shouldReturnNull() {
        AVL tree = getSampleAVLTree();
        int notExistingKey = 11;
        AVL.Node result = tree.find(notExistingKey);
        Assert.assertNull(result);
    }

    @Test
    public void givenEmptyTree_whenDeleteCalled_treeShouldBeAvl() {
        AVL tree = getSampleAVLTree();
        System.out.println(tree.getHeight());
        tree.delete(1);
        tree.delete(5);
        System.out.println(tree.getHeight());
        Assert.assertTrue(isAVL(tree));
    }

    @Test
    public void givenSampleTree_whenDeleteCalled_treeShouldBeAvl() {
        AVL tree = getSampleAVLTree();
        tree.delete(1);
        Assert.assertTrue(isAVL(tree, tree.getRoot()));
    }

    private boolean isAVL(AVL tree) {
        return isAVL(tree, tree.getRoot());
    }

    private boolean isAVL(AVL tree, AVL.Node node) {
        if ( node == null )
            return true;
        int balance = tree.getBalance(node);
        return (balance <= 1 && balance >= -1) &&  isAVL(tree, node.child[0]) && isAVL(tree, node.child[1]);
    }

    private AVL getSampleAVLTree() {
        AVL avlTree = new AVL();
        for (int i = 0; i < 10; i++)
            avlTree.insert(i);
        return avlTree;
    }
    @Test
    public void checkTree( ){
        AVL tree = new AVL();
        for (int i = 1; i < 10; i++)
            tree.insert(i);

        for(int i=1;i<10;++i){
            AVL.Node result = tree.find(i);
            Assert.assertNotNull(result);
        }
        System.out.println(tree.getHeight());
        tree.delete(5);
        System.out.println(tree.getHeight());
        //tree.printTree();
        tree.BFSPrint(tree.getRoot());
    }
}
