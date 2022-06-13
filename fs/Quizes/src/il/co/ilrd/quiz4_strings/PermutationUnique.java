package il.co.ilrd.quiz4_strings;

import java.util.*;

public class PermutationUnique {
   private ArrayList<String> perms;
   private HashMap<Character,Integer> hashMap;

   public PermutationUnique(){
       perms = new ArrayList<>();
       hashMap = new HashMap<>();
   }
    public ArrayList<String> printPerms(String s){
        ArrayList<String> result = new ArrayList<>();
        hashMap = buildFreqTable(s);
        printPerms(hashMap, "", s.length(),result);
        return result;
    }
    public HashMap<Character,Integer> buildFreqTable(String s){
        HashMap<Character,Integer> map = new HashMap<>();
        for(char c: s.toCharArray()){
            map.merge(c,1,Integer::sum);
        }
        return map;
    }

    public void printPerms(HashMap<Character,Integer> map, String prefix, int remain, ArrayList<String> result){
        if(remain == 0){
            result.add(prefix);
            return;
        }
        ArrayList<Set<String>> test = new ArrayList<Set<String>>();
        for(Character c: map.keySet()){
            int count =  map.get(c);
            if(count > 0){
                map.put(c,count -1);
                printPerms(map, prefix + c, remain - 1, result);
                map.put(c,count);
            }
        }
    }
    public static void main(String[] args){
        PermutationUnique test = new PermutationUnique();
        test.perms = test.printPerms("lab");
        System.out.println(test.perms);
        System.out.println(test.hashMap.values());
        System.out.println(test.hashMap.keySet());
    }


}
