package il.co.ilrd.dsexam;
//insert to binary search tree
public class Question13 {
    public static Node root;

    public Question13() {}


    public void insert(int data){
        if(root == null){
            root =  new Node(data);
            return;
        }

        Node runner = root;
        Node parent = runner;
        Node newNode = new Node(data);

        while (runner != null) {
            parent = runner;
            runner = runner.children[whichChild(runner, data)];
        }
        parent.children[whichChild(runner, data)] = newNode;
    }

    public Node insertRec(int data){
        return insertRec(root,data);
}
    private Node insertRec(Node node, int data) {
        if (node == null) {
            node =  new Node(data);
        }
        else
            node.children[whichChild(node, data)] = insertRec(node.children[whichChild(node, data)], data);

        return node;
    }

    private int whichChild(Node node, int data) {
        if (node.data == data)
            throw new RuntimeException("duplicate!!");
        if (node.data > data)
            return 0;
        return 1;

    }
    private void printTree(Node node) {
        if(node == null)
            return;

        printTree(node.children[0]);
        System.out.print(node.data + " ");
        printTree(node.children[1]);
    }

    protected class Node {
        Integer data;
        Node[] children = new Node[2];

        public Node(int data) {
            this.data = data;
            children[0] = null;
            children[1] = null;
        }
    }

    public static void main(String[] args) {
        Question13 test = new Question13();
        Node head = test.insertRec(14);
        test.insertRec(head,3);
        test.insertRec(head,16);
        test.insertRec(head,15);

        for (int i = 6; i < 10; ++i)
            test.insertRec(head, i);

        test.printTree(head);
        System.out.println();
        test.insert(17);
        test.printTree(head);
    }
}
