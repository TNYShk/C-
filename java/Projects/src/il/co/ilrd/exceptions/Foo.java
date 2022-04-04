package il.co.ilrd.exceptions;

import java.io.IOException;
import java.lang.Throwable;
import java.lang.Exception;
public class Foo {
    Boolean obj = null;

public void func1() throws Exception {
    try{
        int ans = 50/0;
    }catch(Exception e){
        int data2 = 70/0;
    }
    System.out.print("enclosing exception in both try and catch blocks");
}
    public void func2() {
        System.out.println("inside func2, outside try");
        try {
            obj.toString();

            }catch(NullPointerException e) {

             e.printStackTrace();
            throw new NullPointerException("Tanya's NUllpointer");
            }
            obj = true;
            System.out.println("inside func2, trying!");
        }

    public void func3(){
        byte arry[] = new byte[100];

        try{
            arry[101] = 1;
        } catch (Exception e){
            System.out.println("func3 inside catch block!");
            //sSystem.err.println(e);
            e.printStackTrace();
        }
        System.out.println("func3 end!");
    }
    public void divideIt(double a, double b)   {
        //double arr[] = new double[5];
        double ans = 0;

        try {
            ans = (a / b);
            if (b == 0){
                throw new ArithmeticException("cant divide by zero!");
            }
        } catch (Exception cause) {
            System.out.println("ans is :" + ans);
            StackTraceElement elements[] = cause.getStackTrace();

            for (int i = 0, n = elements.length; i < n; i++) {
                System.err.println(elements[i].getFileName()
                        + ":" + elements[i].getLineNumber()
                        + ">> "
                        + elements[i].getMethodName() + "()");
            }
        }
        b = 7;
        try{
            ans = (a / b);
            System.out.println("another try " + ans);

        } catch (Exception e){
            System.out.println("something to catch?");
            System.err.println(e);
        }
        System.out.println("ans is "+ ans);
        System.out.println("end of dive");
    }

    public static void main(String []args) {
        Foo fi = new Foo();

        try{
            fi.func2();
        } catch (Exception cause){
            StackTraceElement elements[] = cause.getStackTrace();

        for (int i = 0, n = elements.length; i < n; i++) {
            System.err.println(elements[i].getFileName()
               + ":" + elements[i].getLineNumber()
               + ">> "
               + elements[i].getMethodName() + "()");
        }
        }finally {
            System.out.println("finally can move on");
        }

        fi.func3();
        try{
            fi.func1();
        } catch(Exception e){
            System.out.println("func1");
            System.err.println(e);
        }
        try{
            fi.divideIt(3,'א');
            fi.divideIt(15,0.0);
        }catch( Exception e){
            e.printStackTrace();
        }

        Delete ichs = new Delete();
        try{
            ichs.func4();
        }catch(Exception e){
            System.err.println(e);
        }
    }
}
