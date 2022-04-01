package il.co.ilrd.strquiz;

public class StringQ {

    private static String printReverse(String str) {
        int size = str.length();
        StringBuilder dest = new StringBuilder((size));

        for (int i = (size - 1); i >= 0; --i) {
            dest.append((str.charAt(i)));
        }

        return dest.toString();
    }

    private static boolean isPalindrome(String str){
        StringBuilder dest = new StringBuilder((str));
        dest = dest.reverse();

        return dest.toString().equals(str);
    }

    private static void Permutations(String prefix, String str){

        if(0 == str.length()){
           System.out.print(prefix + " " );
            return;
        }

        int length = str.length();
        for (int i = 0; i < length; ++i) {
            Permutations(prefix + str.charAt(i), str.substring(0, i) + str.substring(i + 1, length));
        }

    }
    private static void printAllPermutations(String str){

        Permutations("", str);
    }


    public static void main(String[] args) {


        System.out.println(StringQ.printReverse("hello there!"));
        System.out.println("is palindrome? "+ isPalindrome("12421"));
        System.out.println("is palindrome? "+ isPalindrome("acbbca"));
        System.out.println("is palindrome? "+ isPalindrome("1"));
        System.out.println("is palindrome? "+ isPalindrome("12"));
       printAllPermutations("ABC");

    }
}