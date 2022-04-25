package il.co.ilrd.quiz14_algebrictree;

public class Node<T> {
    private T data;
    private Node<T> left;
    private  Node<T> right;

    public Node (T data) {
        this.data = data;
    }

    public Node<T> getLeft() {
        return left;
    }

    public Node<T> getRight() {
        return right;
    }

    public void setLeft(Node left) {
        this.left = left;
    }

    public void setRight(Node right) {
        this.right = right;
    }

    public T getData() {
        return data;
    }
    public void setData(T data){
        this.data = data;
    }
}
