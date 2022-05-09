package il.co.ilrd.dsexam;
import java.io.File;
public class Question10 {

    static char[] charArray;

    public static  void printPermutation(String str){
       /* byte[] fileBytes = null;
        try(InputStream input = new FileInputStream("/Users/tanyashkolnik/Documents/Education/Infinity/words.txt")) {
            fileBytes = input.readALlBytes();
        }
        Reader inputStreamReader = new InputStreamReader(inputStream);*/

        Permutations("", str);
}
    private static void Permutations(String prefix, String str){
        if(0 == str.length()){
            if(checkDictionary(prefix))
                System.out.print(prefix + " ");
            return;
        }

        int length = str.length();
        for (int i = 0; i < length; ++i) {
            Permutations(prefix + str.charAt(i), str.substring(0, i) + str.substring(i + 1, length));
        }
    }

    private static void printAllPermutation(String str) {
        int start = 0;
        int end = str.length() - 1;
        charArray = str.toCharArray();
        printAllPermutationRec( start, end);
    }

    private static void printAllPermutationRec( int start, int end) {
        if (start == end) {
            if(checkDictionary(charArray))
                System.out.println(charArray);
            return;
        }
        for (int i = start; i <= end; ++i) {
            charArray = swap( start, i);
            printAllPermutationRec( start + 1, end);
            charArray = swap( start, i);
        }
    }

    private static char[] swap( int start, int end) {
        char tmp = charArray[start];
        charArray[start] = charArray[end];
        charArray[end] = tmp;

        return charArray;
    }


    private static boolean checkDictionary(String prefix){
        return prefix.length() == 5;
    }
    private static boolean checkDictionary(char[] prefix){
        return prefix.length == 5;
    }

    public static void main(String[] args){
        String str = "tasty";
        printPermutation(str);
        String str1 = "fault";

        printAllPermutation(str);
        printAllPermutation(str1);

    }
}
