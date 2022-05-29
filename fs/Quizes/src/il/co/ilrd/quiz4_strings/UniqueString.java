package il.co.ilrd.quiz4_strings;

public class UniqueString {
    public static boolean isUnique(String str) {
        if (str.length() > 128)
            return false;
        boolean[] charSet = new boolean[128];
        char[]tt = str.toCharArray();

        for (int i = 0; i < str.length(); ++i) {
            int temp = str.charAt(i);
            if (charSet[temp])
                return false;
            charSet[temp] = true;
        }
        return true;
    }
    /* check for unique chars using bitwise operations*/
    public static boolean isUniqueChar(String str) {
        int checkAgainst = 0;
        for (int i = 0; i < str.length(); ++i) {
            int temp = Character.toLowerCase(str.charAt(i)) - 'a';

            if ((checkAgainst & (1 << temp)) > 0) {
                System.out.println("duplicate: " + str.charAt(i));
                return false;
            }
            checkAgainst |= (1 << temp);

        }
        return true;
    }
    /* check if 2 strings are permutations of each other*/
    public static boolean Permutations(String s1, String s2) {
        if (s1.length() != s2.length())
            return false;

        int[] letters = new int[128];
        for(int j = 0; j<s1.length();++j)
            letters[s1.charAt(j)]++;

        for (int i = 0; i < s2.length(); ++i) {
            int cc = s2.charAt(i);
            if (--letters[cc] < 0)
                return false;
        }

        return true;
    }

    /* check if a given string sentence is permutation of palindrome*/
    public static boolean isPermutationOfPalindrome(String phrase){
        int countOdd = 0;
        int[] lut =  new int['z' - 'a' + 1];
        for(char c: phrase.toCharArray()){
            int x = getCharNumber(c);
            if(x != -1){
                lut[x]++;
                if(lut[x] % 2 ==1){
                    countOdd++;
                }else{
                    countOdd--;
                }
            }
        }
        return countOdd <= 1;
    }

    static int getCharNumber(char c){
        int a = Character.getNumericValue('a');
        int z = Character.getNumericValue('z');
        int val = Character.getNumericValue(c);
        if( a<= val && val <= z)
            return val - a;
        return -1;
    }

    /* bitwise solution to the above*/

    public static boolean isPermutationPlandromeBitwise(String sent){
        int bitVector = 0;
        for(char c: sent.toCharArray()){
            int x = getCharNumber(c);
            bitVector = toggle(bitVector,x);
        }
        return bitVector == 0 || checkExactlyOneBitSet(bitVector);
    }

    static int toggle(int bitVector, int idx){
        if(idx < 0) return bitVector;

        int mask = 1 << idx;
        System.out.println("mask : " + mask);
        if ((bitVector & mask) == 0){
            bitVector |= mask;
        }else{
            bitVector &= ~mask;
        }
        System.out.println("bitVec : " + bitVector);
        return bitVector;
    }

    static boolean checkExactlyOneBitSet(int bitVector){
        return (bitVector & (bitVector -1) )==0;
    }

    static boolean OneEditAway(String first, String second){
        if (Math.abs(first.length() - second.length()) > 1)
            return false;

        String s1 = (first.length() < second.length()) ? first:second;
        String s2 = (first.length()  < second.length()) ? second:first;

        boolean isDifference = false;
        int i = 0,j = 0;
        while( j< s2.length() && i < s1.length()){
            if(s1.charAt(i) != s2.charAt(j)){
                if(isDifference) return false;
                isDifference = true;

                if(s1.length() == s2.length()){
                    i++;
                }
            }else{
                i++;
            }
            j++;
        }
        return true;
    }
    public static String compress(String str){
        StringBuilder compress = new StringBuilder();
        int countConsecutive = 0;

        for(int i = 0; i< str.length() ;++i){
            ++countConsecutive;

            if( i+1 >= str.length() ||  str.charAt(i) != str.charAt(i+1)){
                compress.append(str.charAt(i));
                if(countConsecutive>1)
                    compress.append(countConsecutive);
                countConsecutive = 0;
            }
        }
        //return String.valueOf(compress);
        return compress.length() < str.length()? String.valueOf(compress) : str;
    }
    public static void main(String[] args) {
        String test = "tatyanna";
        String perm = "abcdr";
        //System.out.println(isUnique(test));
        //System.out.println(isUniqueChar(test));
        /*System.out.println(Permutations(perm, "radcb"));
        System.out.println(Permutations(perm, "tatya"));
        System.out.println(Permutations(perm, test));*/
        String permpalin = "tactcoapapa";
        //System.out.println(isPermutationOfPalindrome(permpalin));
        // System.out.println(isPermutationPlandromeBitwise(permpalin));


        System.out.println(OneEditAway("sale","apple"));

        System.out.println(OneEditAway("sale","sales"));
        System.out.println(compress("aaabcccccccaa"));
        System.out.println(compress("tatyannnna"));
       /* int a = Character.getNumericValue('t');
        System.out.println(a);*/
    }
}
