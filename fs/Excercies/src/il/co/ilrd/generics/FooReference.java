package il.co.ilrd.generics;

public class FooReference<T> {
    private T data;

    public FooReference(T data){
        this.data = data;
    }

    public void setData(T data){
        this.data = data;
    }

    public T getData(){
        return this.data;
    }
    @Override
    public String toString(){
        return data + " ";
    }
}
