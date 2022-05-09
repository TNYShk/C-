package il.co.ilrd.dsexam;
import java.io.*;
import java.util.HashSet;

/*
    english dictionary loaded into hashSet,
    each input string permutates
    only available words (in the dictionary) are printed.
    WORDLE here we go:)
 */
public class Question10 {

    private static char[] charArray;
    private static HashSet<String> dictionary = new HashSet<>();


    private static void loadDictionary(){

    }
    public static boolean findInDictionary(String word) throws IOException {
        try( BufferedReader rd = new BufferedReader( new FileReader ("/Users/tanyashkolnik/Documents/Education/Infinity/words.txt"))) {
            String line;
            int i = 0;
            while ((line = rd.readLine()) != null) {
                dictionary.add(line);
                i++;
            }
        }
        return dictionary.contains(word);
    }
    public static void printPermutation(String str) throws IOException {
            Permutations("", str);
        }

    private static void Permutations(String prefix, String str) throws IOException {
        if(0 == str.length()){
            if(findInDictionary(prefix))
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

    private static void printAllPermutationRec( int start, int end){
        if (start == end) {
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




    public static void main(String[] args) throws IOException {
        String str = "taste";
        printPermutation(str);
        //String str1 = "fault";

        printAllPermutation(str);
       // printPermutation("fault");
        //printAllPermutation(str1);

    }
}
