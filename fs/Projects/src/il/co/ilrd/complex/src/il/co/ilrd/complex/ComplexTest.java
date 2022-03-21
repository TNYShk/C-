package il.co.ilrd.complex;

import org.junit.jupiter.api.Test;

import static il.co.ilrd.complex.Complex.parse;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;
public class ComplexTest {

    public static void main(String args[]){
       TestUno();
       ParseTest();
        JuintTst tanya = new JuintTst();
        tanya.testEmptyNull();
    }


    static void TestUno(){

        Complex igal = new Complex(1,2);
        Complex twinky = new Complex(2,4);
        Complex kika = new Complex(2,4);
        Complex maya = new Complex(0,-4);
        Complex adam = new Complex(-2,0);
        System.out.println(igal);
        System.out.println(twinky);
        System.out.println("twinky VS igal: " + igal.equals(twinky));
        System.out.println("twinky VS kika: " + kika.equals(twinky));
        System.out.println("twinky hash "+ twinky.hashCode());
        System.out.println("kika hash "+ kika.hashCode());
        System.out.println("maya: " + maya);
        System.out.println("adam: " + adam);
        System.out.println("maya hash "+ maya.hashCode());
        System.out.println("adam hash "+ adam.hashCode());
        System.out.println("maya VS adam: " + maya.equals(adam));
        System.out.println("dividing 2 complex nums:" + igal.divideBy(twinky));
        System.out.println("adding 2 complex nums:" +  igal.addition((twinky)));
        twinky = igal.addition((twinky));
        System.out.println(twinky);
        System.out.println(igal);
    }

    static void ParseTest(){
        System.out.println("\nParsing test!");
        System.out.println(parse("-26 - 8i"));
        System.out.println(parse("0.3 + 0.0i"));
        System.out.println(parse("0 - 0.5i"));
        System.out.println(parse("-0.6 + 8i"));
    }
}
class JuintTst{

    @Test
    static void testEmptyNull(){
        Complex tanya = new Complex(1,2);
        Complex maya = new Complex(0,-4);


        Complex twinky = new Complex(2,4);
        Complex kika = new Complex(2,4);

        Complex adam = new Complex(-2,0);
        assertEquals(true,tanya.isReal());
        assertEquals(false,maya.isReal());
        assertEquals(false,adam.isImaginary());
        tanya.setReal(0.0);
        tanya.setImaginary(0.0);
        assertNull(twinky.divideBy(tanya));
        System.out.println("twinky vs kika: compare to " + twinky.compareTo(kika));
        System.out.println("twinky vs maya: compare to " + twinky.compareTo(maya));
        System.out.println("adam vs maya: compare to " + adam.compareTo(maya));
        System.out.println("equals and assert null done!\n");

    }
}
