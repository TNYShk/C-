package tcode;

public class ClimbStairs {
    public static int climbIt(int n){
        int a = 1, b = 1;
        while(n-- > 0) {
            a = (b += a) - a;
            System.out.println("way: "+ a +" b: "+ b);
        }
        return a;
    }

    public static void main(String[] args){
        System.out.println(climbIt(4));
    }
}
