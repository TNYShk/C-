package il.co.ilrd.q4;


class Base {
   /* public Base(){
        System.out.println("Base ");
    }
    public Base(String s){
        System.out.println("Base " + s);
    }*/
    public void test(){
        System.out.println("Base");
    }
}
class Base1 extends Base{
    public void test(){
        System.out.println("Base1");
    }
}
class Base2 extends Base{
    public void test(){
        System.out.println("Base2");
    }
}

class Derived extends Base{
    public Derived(String s){
       // super(); //statement 1
       // super(s); //statement 2
        System.out.println("Derived");
    }
}
/*
class DeriDerived extends Derived{
    public DeriDerived(){
        System.out.println("DeriDerived");
    }
}*/

class Test{
    public static void main(String []args){
        //Derived b = new DeriDerived();
        //Base a = new Derived("Hello ");
        Base obj = new Base1();
        ((Base2)obj).test(); //cast

        Base ob = new Base2();
        ((Base2)ob).test(); //cast
    }
}