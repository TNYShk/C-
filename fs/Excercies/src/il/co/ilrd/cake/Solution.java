package il.co.ilrd.cake;

import org.testng.annotations.Test;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;


public class Solution {

    public static int strStr(String haystack, String needle) {
        // If needle is an empty string
        if(needle == null) return -1;
        if (needle.isEmpty()) return 0;

        // If the needle is not within the haystack
        if (!haystack.contains(needle)) return -1;

        // declare an index and the needle's length
        int index = 0;
        int len = needle.length();

        // loop through the hackstack minus the needle's length
        for (int i = 0; i <= haystack.length() - len; i++) {
            // compare the needle with the hackstack new string
            // created from using substring, start->end
            if (haystack.substring(i, i + len).equals(needle)) {
                // set the index and exit
                index = i;
                break;
            }
        }
        if(haystack.length()%needle.length() == 0 ){
           // System.out.print("needle: " + needle + "\t");
            return haystack.length()/needle.length();
        }
        return index;
    }

    public static int bruteForce(String x)
    {
        StringBuffer cake = new StringBuffer(x);
        String[] brute = new String[100];
        int first = x.indexOf(cake.charAt(0));
        int second = x.indexOf(cake.charAt(0), first +1);

        for(int i = 0; second + i<= x.length(); ++i){
            brute[i] = cake.substring(first,second +i);
            System.out.println(brute[i]);
        }
        int max = 1;
        int occurance[] = new int[x.length()];
        for(int i = 0 ; i< x.length(); ++i){
            int bla = strStr(x,brute[i]);
            if(bla > max){
                max = bla;
            }
            occurance[i] = bla;
            //System.out.print(strStr(x,brute[i]) );
         }
        System.out.print("max is: " + Arrays.stream(occurance).max());
        System.out.print("min is: " + Arrays.stream(occurance).min());
        return max;
    }

    public static int solution(String x){

        return bruteForce(x);



                }



    public static void main(String []args){
        /*String test =  "abccbaabccba";
        System.out.println("ans "+ solution(test));

        String another = "abccbaabccba";
        System.out.println("ans "+ solution(another));

        String neby = "abcabcabcabc";
        System.out.println("ans "+ solution(neby));

        String four = "abcabcabcabc";
        System.out.println("ans "+ solution(four));*/

        String five = "abcfcabccabcfcabcc";
        System.out.println("ans "+ solution(five));
    }



}
