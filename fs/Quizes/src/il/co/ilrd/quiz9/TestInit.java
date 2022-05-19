package il.co.ilrd.quiz9;


import java.io.*;

class BaseInit{
    private int member1 = 1;
    private int member2 = 2;

    public BaseInit(){
        System.out.println("Base Ctor");
        printFirst();
        printSecond();
    }

    private void printFirst(){
        System.out.println(member1);
    }
    /*
    to fix the issue private access modifier is added to printFirst of Base class.
    thus no method override occurs!
     */
    private void printSecond(){
        System.out.println(member2);
    }
}
class DerivedInit extends BaseInit{
    private int member3 = 3;
    private int member4 = 4;

    public DerivedInit(){
        System.out.println("Derived Ctor");
        printFirst();
        printSecond();
    }
    private void printFirst(){
        System.out.println(member3);
    }
    /*
printFisrt() of DerivedInit clashed with Base's, attempting to assign a weaker access privileges (private) while its package protected
 */
    private void printSecond(){
        System.out.println(member4);
    }
/*
Q3, problem with foo() and how to fix.
count variable hasnt been initialized. a local var of method must be initialized
 */
    public void foo() throws IOException{
        int count = 0;
        if(System.in.read() != -1)
            count++;
        System.out.println("input has "+count+ " chars");
    }
/*
Q4- foo2() wont compile because:
    a. missing InputFileName,OutputFileName variables altogether.
    b. no Exception handling for FileInput/Output= Stream (no catch clause), or exception in method signature
 */
    public void foo2() throws IOException {
        InputStream in = null;
        OutputStream out = null;
        String InputFileName = "haha";
        String OutputFileName = "hihi";
        try{
            in = new FileInputStream(InputFileName);
            out = new FileOutputStream(OutputFileName);
        }finally{
            out.close();
            in.close();
        }
    }
}
public class TestInit {
    public static void main(String[] args) throws IOException {
        DerivedInit d = new DerivedInit();
        d.foo();
    }
}
