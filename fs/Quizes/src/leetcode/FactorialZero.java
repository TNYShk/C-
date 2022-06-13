package leetcode;
//Write an algorithm which computes the number of trailing zeros in n factorial. trailing zero is created with multiples of 10 (5*2)
// its enough to count the 5,2 as pair leading to factorial >> 5! = 2,5 - 1 pair
public class FactorialZero {

    public static  int countFactzero(int factorial){
        if(factorial<5)
            return 0;
        int counter = 0;
        int runner = 5;
        while(runner <= factorial){
            ++counter;
            runner +=5;
            if(runner%25 ==0)
                ++counter;
        }

        return counter;
    }

    public static int countFactZeroes(int num){
        int count = 0;
        if(num<0) return -1;
        for(int i = 5; num/i>0; i *=5){
            count += num/i;
        }
        return count;
    }

    public static void main(String[] args){
        System.out.println(countFactzero(35));
        System.out.println(countFactZeroes(35));
    }
}
