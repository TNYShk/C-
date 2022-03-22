package il.co.ilrd.complex;

import static il.co.ilrd.complex.Complex.parse;

public class ComplexTest {

    public static void main(String[] args){
        Complex parse = parse(" -26 - 8i");
        System.out.println(parse);
        parse = parse(" -26 -8i");
        System.out.println(parse);
        parse = parse(" -26 ");
        System.out.println(parse);
        parse = parse(" -8i");
        System.out.println(parse);
        parse = parse(" 4i");
        System.out.println(parse);
        parse = parse(" 2.6 ");
        System.out.println(parse);
    }

}

