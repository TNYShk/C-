package il.co.ilrd.quiz3;

public class Foo {
    String s = "abc";

    public Foo() {
        System.out.println("Ctor called");
    }

    static {
        System.out.println("static init called");
    }

    {
        System.out.println("instance init called");
    }

    public static void main(String[] args){
        new Foo();
        new Foo();
    }
}
