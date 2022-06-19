package tcode;

public class Fibonacci {

    static int[] cache;
    public int fib(int n) {
        if(n <= 1)
            return n;

        cache = new int[n + 1];
        cache[0] = 0;
        cache[1] = 1;
        cache[2] = 1;

        for(int i = 3; i <= n; i++)
            cache[i] = cache[i - 1] + cache[i - 2];

        //return cache[n];
        return sumIt(n);
    }
    private int sumIt(int n){
        int sum = 0;
        for(int i=1; i<n ;++i){
            sum += cache[i];
        }
        return sum;
    }

    public static void printIt(){
        for(int x: cache)
            System.out.print(x+" ");
        System.out.println();
    }

    public static void main(String[] args){
        Fibonacci test = new Fibonacci();
        System.out.println(test.fib(27));
        printIt();
    }
}
