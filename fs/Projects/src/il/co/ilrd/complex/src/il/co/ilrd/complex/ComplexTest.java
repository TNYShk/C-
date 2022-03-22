package il.co.ilrd.complex;

import org.junit.jupiter.api.Test;

import static il.co.ilrd.complex.Complex.parse;
import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class ComplexTest {

    public static void main(String[] args){

    }


}
/*
class JuintTst{

    @Test
    static void testEmptyNull(){
        Complex tanya = new Complex(1,2);
        Complex maya = new Complex(0,-4);

        Complex twinky = new Complex(2,4);
        Complex adam = new Complex(-2,0);

        assertEquals(true,tanya.isReal());
        assertEquals(false,maya.isReal());
        assertEquals(false,adam.isImaginary());
        tanya.setReal(0.0);
        tanya.setImaginary(0.0);
        assertNull(twinky.divideBy(tanya));
        System.out.println("setVal, Divide by Zero and assert null done!");
        assertTrue(adam.hashCode() < maya.hashCode());
        //System.out.println("twinky vs maya: compare to " + twinky.compareTo(maya));
       // System.out.println("adam vs maya: compare to " + adam.compareTo(maya));
        System.out.println("hashCode Test done!");

    }
    @Test
    static void ParseTest() {

        Complex parse = parse("-26 - 8i");
        Complex original = new Complex(-26, -8);
        assertEquals(parse, original);
        parse = parse("0.3 + 0.0i");
        original = new Complex(0.3, 0);
        assertEquals(parse, original);
        parse = parse("0 - 0.5i");
        original = new Complex(0, -0.5);
        assertEquals(parse, original);
        parse = parse("-0.6 + 8i");
        original = new Complex(-0.6, 8);
        assertEquals(parse, original);

        System.out.println("parse test done!");
    }

    @Test
    static void EqualsCompareToTest() {
        Complex twinky = new Complex(2,4);
        Complex kika = new Complex(2,4);
        assertNotSame(twinky,kika);
        assertEquals(twinky,kika);
        System.out.println("equals,CompareTo Test done!");
    }
    @Test
    static void ComplexOperationsTest(){
        Complex igal = new Complex(1,2);
        Complex twinky = new Complex(2,4);
        Complex maya = new Complex(0,-4);
        double delta = 0.001;
        //System.out.println(igal);
        //System.out.println(twinky);
        Complex div = igal.divideBy(twinky);
        assertEquals(0.5, div.getReal(), delta);
        //System.out.println("dividing 2 complex nums:" + igal.divideBy(twinky));
       // System.out.println("adding 2 complex nums:" +  igal.addition((twinky)));

        twinky = igal.addition((twinky));
        assertEquals(twinky.getReal(),3.0);
        assertEquals(twinky.getImaginary(),6.0);
        twinky = twinky.substract(igal);
        assertEquals(twinky.getReal(),2.0);
        assertEquals(twinky.getImaginary(),4.0);

        igal = igal.multiplyWith(maya);
        assertEquals(igal.getReal(),8.0);
        assertEquals(igal.getImaginary(),-4.0);

        System.out.println("Addition Subtraction Multiplication tests done!");
    }
}*/
