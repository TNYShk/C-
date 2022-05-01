package il.co.ilrd.exam;

public class Q29 {
    int intSuperClass = 10;

    static{
        System.out.println("1 static initializer called of SUPER class");
    }
    {
        System.out.println("1 instance initializer called of SUPER class");
        System.out.println(intSuperClass);
    }
    public Q29(){
        System.out.println("constructor called of SUPER class");
        intSuperClass *=2;
        System.out.println(intSuperClass);
    }
    static{
        System.out.println("2 static initializer called of SUPER class");
    }

    {

            System.out.println("2 instance initializer called of SUPER class");
    }
}

class SubClass extends Q29{
    int intSubClass = 100;

    {
        System.out.println("1. instance initializer called of subclass");
        System.out.println(intSubClass);
    }

    public SubClass(){
        System.out.println("constructor called of subclass");
        System.out.println(intSubClass);
        intSubClass *=2;
    }

    static{
        System.out.println("1. static initializer called of subclass");
    }
    {
        System.out.println("2. instance initializer called of subclass");
    }
    static{
        System.out.println("2. static initializer called of subclass");
    }
    public static void main(String[] args){
        new SubClass();
        new SubClass();
    }
}
