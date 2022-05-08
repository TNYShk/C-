package il.co.ilrd.dsexam;

import java.nio.file.Watchable;

public class Question1 {
    private V element;
    private V[] array;
    private int version;

    public Question1(int size){
        array = new V[size];
        version = 0;
        element = new V(0);
    }
    class V{
        int version = 0;
        int value;

        public V(int val){
            this(0,val);
        }
        private V(int version,int val){
            value = val;
            this.version = ++version;
        }
    }

    public void setVal(int idx, int val){
        ++version;
        array[idx] = new V(val);
    }

    public int getVal(int idx){
        if(element.version < array[idx].version)
            return element.value;
        return array[idx].value;
    }

    public void setAll(int val){
        element.version = ++version;
        element.value = val;
    }


    public static void main(String[] args){
        Question1 test = new Question1(5);
        test.setVal(0,3);
        System.out.println("val is " + test.getVal(0));
        test.setAll(6);
        System.out.println("val is " + test.getVal(0));
        test.setVal(1,25);
        System.out.println("val is " + test.getVal(1));

    }
}
