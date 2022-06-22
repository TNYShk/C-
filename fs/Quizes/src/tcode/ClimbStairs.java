package tcode;
//given int n, how many distinct ways are there to climb n stairs, can take 1 step or 2 steps
public class ClimbStairs {
    public static int climbIt(int n){
        int a = 1, b = 1;
        while(n-- > 0) {
            a = (b += a) - a;
            System.out.println("a: "+ a +" b: "+ b);
        }
        return a;
    }

    public static void main(String[] args){
        System.out.println(climbIt(4));
    }
}
