package il.co.ilrd.exceptions;

import java.io.IOException;

public class Foo {
    Boolean obj = null;

    public void func1() throws IOException{
        System.out.println("inside func1, using throws");
        System.out.println("thrown an IOException!");
        System.out.println("something else to throw!!!");
    }
    public void func2(){
        System.out.println("inside func2, outside try");
        try{
            if(obj)
            {
                System.out.println("inside func2, trying!");
                throw new NullPointerException();
            }
        } catch (NullPointerException e) {
            e.printStackTrace();

        }finally {
            obj = true;
            System.out.println("finally can move on");
        }
    }
    public void func3(){
        byte arry[] = new byte[100];

        try{
            arry[101] = 1;
        } catch (Exception e){
            System.out.println("func3 excepetion is?");
            e.printStackTrace();
        }
    }
    public void divideIt(double a, double b) {
        //double arr[] = new double[5];
        double ans = 0;
        try {
             ans = (a / b);
            System.out.println("try ans is " + ans);
            //arr[5] = ans;
        } catch (NumberFormatException e) {
            e.printStackTrace();
            System.out.println("NumberFormatException");
        } catch (ArrayIndexOutOfBoundsException e) {
            e.printStackTrace();
            System.out.println("ArrayIndexOutOfBoundsException");
        } catch (ArithmeticException e) {
            e.printStackTrace();
            System.out.println("ArithmeticException");
        }
        System.out.println("and is " + ans);
    }
    public static void  main(String []args) throws IOException {
        Foo fi = new Foo();
        fi.func1();
        fi.func2();
        fi.divideIt(3,0);
        fi.divideIt(3,'c');
        fi.func3();
        Delete ichs = new Delete();
        ichs.func4();

    }
}
