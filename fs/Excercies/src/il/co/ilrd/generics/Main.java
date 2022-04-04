package il.co.ilrd.generics;

import java.util.ArrayList;
import java.util.List;

public class Main<T> {
    private List<T> arr;

    public Main(){

    }

    public static void main(String []args){
        TestFoo();

        Main tanya = new Main();
      tanya.arr = new ArrayList<String>();
      tanya.populate("Hello");
        tanya.populate("again");
      Main.printArr(tanya.arr);
      tanya.arr = new ArrayList<Number>();
        tanya.populate(20);
        tanya.populate(202.2);
        Main.printArr(tanya.arr);

    }

    public void populate(T t){
        arr.add(t);
    }
    public static <T> void printArr(List<T> arr){
        System.out.print(arr + " ");
        System.out.println();

    }

    static void TestFoo(){
        FooReference<String> fooya = new FooReference<>("testing");
        System.out.println(fooya);
        fooya.setData("Shoshana");
        System.out.println(fooya.getData());
        FooReference<Integer> fooma = new FooReference<>(8888);
        System.out.println(fooya.getClass());
        System.out.println(fooma.getClass());
        System.out.println(fooma.getData());



    }

}
