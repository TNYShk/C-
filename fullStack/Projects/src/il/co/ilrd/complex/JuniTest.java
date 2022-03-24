package il.co.ilrd.complex;



import org.junit.jupiter.api.Test;

import static il.co.ilrd.complex.Complex.*;
import static org.junit.jupiter.api.Assertions.*;

class JuintTst{

    @Test
    void testEmptyNull(){
        Complex tanya = createReal(1);
        tanya.setImaginary(2);

        Complex maya = createReal(0);
        maya.setImaginary(-4);
        Complex adam = createReal(-2);
        maya.setImaginary(0);

        Complex twinky = createReal(2);
        twinky.setImaginary(4);


        assertEquals(false,tanya.isReal());
        assertEquals(true,maya.isReal());
        assertEquals(false,adam.isImaginary());
        tanya.setReal(0.0);
        tanya.setImaginary(0.0);
        assertNull(twinky.divideBy(tanya));
        System.out.println("setVal, Divide by Zero and assert null done!");
        assertTrue(adam.hashCode() < maya.hashCode());
        maya.setReal(2);
        maya.setImaginary(4);
        assertTrue(twinky.hashCode() == maya.hashCode());
        assertTrue(twinky.compareTo(maya) == 0);

        System.out.println("hashCode Test done!");

    }
    @Test
    void ParseTest() {

        Complex parse = parse(" -26 +8i");
        Complex original = createReal(-26);
        original.setImaginary(8);
        assertEquals(parse, original);

        parse = parse("5+ 0.3i");
        original.setReal(5);
        original.setImaginary(0.3);
        assertEquals(parse, original);
        parse = parse(" 5 + 0.3i");
        original.setReal(5);
        original.setImaginary(0.3);
        assertEquals(parse, original);

        parse = parse("  0.3  ");
        original.setReal(0.3);
        original.setImaginary(0);
        assertEquals(parse, original);

        parse = parse(" -0.5i");
        original.setReal(0);
        original.setImaginary(-0.5);
        assertEquals(parse, original);

        parse = parse("-0.6 + 8i");
        original.setReal(-0.6);
        original.setImaginary(8);
        assertEquals(parse, original);

        parse = parse("240 -8i");
        original.setReal(240);
        original.setImaginary(-8);
        assertEquals(parse, original);

        parse = parse(" 42 - 0.8i");
        original.setReal(42);
        original.setImaginary(-0.8);
        assertEquals(parse, original);

        System.out.println("parse test done!");
    }

    @Test
    void EqualsCompareToTest() {
        Complex twinky = createReal(2);
        twinky.setImaginary(4);
        Complex kika = createReal(2);
        kika.setImaginary(4);

        assertNotSame(twinky,kika);
        assertEquals(twinky,kika);
        assertTrue(kika.hashCode() == twinky.hashCode());
        assertTrue(twinky.compareTo(kika) == 0);
        System.out.println("equals,CompareTo Test done!");
    }
    @Test
    void ComplexOperationsTest(){
        Complex igal = createReal(1);
        igal.setImaginary(2);
        Complex twinky = createReal(2);
        twinky.setImaginary(4);
        Complex maya = createImaginary(-4);
        maya.setReal(0);

        double delta = 0.001;
        Complex div = igal.divideBy(twinky);
        assertEquals(0.5, div.getReal(), delta);
        div = maya.divideBy(igal);

        assertEquals(-0.8, div.getImaginary(), delta);
        assertEquals(-1.6, div.getReal(), delta);
        twinky = igal.addition((twinky));
        assertEquals(twinky.getReal(),3.0);
        assertEquals(twinky.getImaginary(),6.0);
        twinky = twinky.substract(igal);
        assertEquals(twinky.getReal(),2.0);
        assertEquals(twinky.getImaginary(),4.0);

        igal = igal.multiplyWith(maya);
        assertEquals(igal.getReal(),8.0);
        assertEquals(igal.getImaginary(),-4.0);

        System.out.println("Addition Subtraction Multiplication Division tests done!");
    }

    @Test
    void testHashCode() {
        Complex z1 = createReal(6.5);
        z1.setImaginary(8);
        Complex z2 = createReal(6.5);
        z2.setImaginary(8);

        assertTrue(z1.equals(z2));
        int n1 = z1.hashCode();
        int n2 = z2.hashCode();
        assertTrue(n1 == n2);

        Complex z3 = createReal(7);
        z3.setImaginary(8);
        int n3 = z3.hashCode();
        assertTrue(n1 != n3);

        Complex z4 = createReal(0.8);
        z4.setImaginary(0);
        Complex z5 = createReal(0);
        z4.setImaginary(0.8);

        int n4 = z4.hashCode();
        int n5 = z5.hashCode();
        assertTrue(n4 != n5);

        Complex z6 = createReal(0);
        z6.setImaginary(7.2);
        Complex z7 = createReal(0);
        z7.setImaginary(0.8);
        int n6 = z6.hashCode();
        int n7 = z7.hashCode();
        assertFalse(n6 == n7);

        System.out.println("Hashing equals tests done!");


    }
}
