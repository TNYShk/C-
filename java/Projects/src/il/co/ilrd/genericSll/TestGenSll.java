package il.co.ilrd.genericSll;

import java.util.ArrayList;
import java.util.List;

public class TestGenSll {


    public static void main(String []args){

        GenericList<String> genlist = new GenericList<>();
        genlist.pushFront("Hi");
        genlist.pushFront("my");
        genlist.pushFront("name");
        genlist.pushFront("is");
        genlist.pushFront("Slim Shady");
        System.out.println("size of list is " + genlist.size());

        //TestStam();



    }

    static void TestStam(){
        List<String> v = new ArrayList<>();
        v.add("hello");
        String s = v.get(0);
        System.out.println(s);
    }
}
