package il.co.ilrd.complex;

public class ComplexTest {

    public static void main(String args[]){
        Complex tanya = new Complex(1,2);
        Complex twinky = new Complex(2,4);
        System.out.println(tanya);
        System.out.println(twinky);
        Complex division = tanya.divideBy((twinky));

        System.out.println("dividing 2 complex nums:" + division);
        System.out.println("adding 2 complex nums:" +  tanya.addition((twinky)));
        twinky = tanya.addition((twinky));
        System.out.println(twinky);
        System.out.println(tanya);
    }
}
