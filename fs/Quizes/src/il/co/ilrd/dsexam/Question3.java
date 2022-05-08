package il.co.ilrd.dsexam;

public class Question3 {
   // static char[] array = {'a','b','&','%','7','8','$'};
    static int[] LUT = new int[256];

    public static boolean isCharThere(char[] arr, char toFind){
        LUT = new int[256];

        for(int i =0; i< arr.length;++i)
            LUT[arr[i]] = 1;

        return LUT[toFind] == 1;
    }

    public static void main(String[] args){
        char[] array = {'a','b','&','%','7','8','$'};

        System.out.println(isCharThere(array,'*'));
        System.out.println(isCharThere(array,'8'));

    }
}
