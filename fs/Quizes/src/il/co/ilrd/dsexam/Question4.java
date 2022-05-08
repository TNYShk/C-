package il.co.ilrd.dsexam;

public class Question4 {
    static char[] array = {'a','c','b','d'};

    public static void cicrularShift( int n){
        reverse(0,array.length-1);
        reverse(0,n-1);
        reverse(n,array.length-1);
    }

    private static void reverse(int from, int to){
        while(from<to) {
            Swap(from, to);
            ++from;
            --to;
        }
    }

    private static void Swap(int a, int b){
        char temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    public static void main(String[] args){
        System.out.println(array);
        cicrularShift(3);
        System.out.println(array);
    }
}
