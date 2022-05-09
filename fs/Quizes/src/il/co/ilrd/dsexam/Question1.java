package il.co.ilrd.dsexam;

import java.nio.file.Watchable;

public class Question1 {
    private V element;
    private V[] array;
    private int version;

    public Question1(int size){

        version = 0;
        element = new V();
        array = new V[size];
        for(int i =0; i<size;++i){
            array[i] = new V();

        }
    }
    private class V{
        int ver;
        int value;

    }

    public void setVal(int idx, int val){
        array[idx].value = val;
        ++version;

    }

    public int getVal(int idx){
        if(version < array[idx].ver)
            return element.value;
        return array[idx].value;
    }

    public void setAll(int val){
        element.ver = version;
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
