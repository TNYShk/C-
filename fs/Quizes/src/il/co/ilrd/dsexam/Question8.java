package il.co.ilrd.dsexam;

public class Question8 {


    public static int multiply(int a, int b){
        int small = Math.min(a,b);
        int big = Math.max(a,b);
        if(a==0 || b==0)
            return 0;
        return reallyMultiply(big, small);
    }
    private static int reallyMultiply(int big, int small){
        if(small == 1)
            return big;
        return reallyMultiply(big, small-1)+ big;
    }

    public static int divideIt(int a, int b){
        if(b==0)
            throw new ArithmeticException();
        if(a==0)
            return 0;
        int result = reallyDivide(Math.abs(a), Math.abs(b));
        return result;
    }

    private static int reallyDivide(int a, int b){
        if(a<b)
            return 0;
        if(a-b == 0)
            return 1;

        return (1 + reallyDivide((a-b),b));
    }

    public static int incrementByOne(int num){
        if((num&1)==0)
            return num|1;
        return incrementByOne(num>>1)<<1;
    }


    public static void main(String[] args){
        System.out.println(divideIt(6,2));
        System.out.println(incrementByOne(7));

        System.out.println(multiply(7,3));
    }
}
