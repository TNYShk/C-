package il.co.ilrd.quiz5;

public class Test {
    public static void main(String[] args){


        System.out.print(func());
    }
    static  int x = 5;

    static int func(){
        int x = 10;
        return --Test.x;
    }


}
