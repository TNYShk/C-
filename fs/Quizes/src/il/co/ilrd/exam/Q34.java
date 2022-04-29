package il.co.ilrd.exam;

public class Q34 {
    public int sumOf(int n){
        Integer sum = 0;
        for(Integer i = 1; i<=n; ++i){
            sum +=i;
        }
        return sum;
    }

    public static void main(String[] args){
        Q34 test = new Q34();
        System.out.println(test.sumOf(4));
    }
}
