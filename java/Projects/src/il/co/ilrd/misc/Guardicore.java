package il.co.ilrd.misc;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;

public class Guardicore {
   private HashMap<Character,Character> myMap;
   private static HashSet<String> wordB = new HashSet<>();
   private int small;
   private int large;

   public Guardicore(){
       myMap = new HashMap<>();
       small = 1;
       large = 5;
   }
   //string egg, add = true
    //string foo, bar = false

   public boolean isIsomorphic(String s, String t){
       int len = (s.length() == t.length())? s.length()-1: 0;
       while(len > 0){
           if(!myMap.containsKey(s.charAt(len))){
               myMap.put(s.charAt(len), t.charAt(len));
           }

           else if(!myMap.get(s.charAt(len)).equals(t.charAt(len))){
               return false;
           }
           --len;
       }
       return true;
   }

   public boolean canItFit(int small, int big, int goal){
       int max = small + (large * big);
       if(max < goal)
           return false;
       return (goal % large <= small);
   }

   public boolean wordBreak(String s, List<String> wordDict) {
       StringBuilder sbuild = new StringBuilder(s);
       int i= 0;
        int total = 0;
       for(String t: wordDict){
           //System.out.println(t);
           int len = i + t.length();
           if(s.substring(i,len).equals(t)){

               wordB.add(s.substring(i,len));
               System.out.println(s.substring(i,len));
               i+=t.length();
           }
           else{
               return false;
           }
            total +=t.length();
           System.out.println(i);
       }

       return i==total;
   }

   public static void main(String[] args){
       Guardicore test = new Guardicore();
      /* System.out.println("is? "+ test.isIsomorphic("egg","add"));
       System.out.println("is? "+ test.isIsomorphic("foo","bar"));
       System.out.println(test.canItFit(3,2,9));
       System.out.println(test.canItFit(3,2,10));
       System.out.println(test.canItFit(3,1,8));*/
       List<String> wordbreak = new ArrayList<>();
       wordbreak.add("cats");
       wordbreak.add("dog");
       wordbreak.add("sand");
       wordbreak.add("and");
       wordbreak.add("cat");
       test.wordBreak("catsandog",wordbreak);
   }
}
