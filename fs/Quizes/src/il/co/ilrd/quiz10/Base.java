package il.co.ilrd.quiz10;

public abstract class Base {
    public Base(){
        System.out.println("in Base");
        foo();
    }

    public void foo(){
        System.out.println("Need to implement by "+ getName());
    }

    abstract public String getName();
}


