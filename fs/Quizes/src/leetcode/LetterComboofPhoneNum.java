package leetcode;

import java.util.*;

public class LetterComboofPhoneNum {
    static HashMap<Character,String> phonebook = new HashMap<>(10);
    private HashMap<Character,Integer> hashMap = new HashMap<>();

    public List<String> letterCombinations(String digits) {
        phonebook = initHash(phonebook);
        Set<String> result = new HashSet<>();
        StringBuilder options = new StringBuilder();
        for(int i=0;i<digits.length();++i){
            options.append(phonebook.get(digits.charAt(i)));
        }
        hashMap = buildFreqTable(options.toString());
        getPerms(hashMap, "", digits.length(),result);
        List<String> answer = new ArrayList<>(result);
        return answer;
    }

    private HashMap<Character,Integer> buildFreqTable(String s){
        HashMap<Character,Integer> map = new HashMap<>();
        for(char c: s.toCharArray()){
            map.merge(c,1,Integer::sum);
        }
        return map;
    }
    public void getPerms(HashMap<Character,Integer> map, String prefix, int remain,
                         Set<String> result){
        if(remain == 0 && !result.contains(prefix)){
            if(!hasInPhoneBook(prefix))
                result.add(prefix);
            return;
        }
        for(Character c: map.keySet()){
            int count =  map.get(c);
            if(count > 0){
                map.put(c,count -1);
                getPerms(map, prefix + c, remain - 1, result);
                map.put(c,count);
            }
        }
    }

    private boolean hasInPhoneBook(String prefix){
        for(String s: phonebook.values()) {
            int i = 0;
            while (s.contains(prefix.substring(++i)) && i < prefix.length()) {
                if (s.contains(prefix)) {
                    return true;
                }
            }
        }
        return false;
    }

    private HashMap<Character,String> initHash(HashMap<Character,String> map){
        map.put('0',"");
        map.put('1',"");
        map.put('2',"abc");
        map.put('3',"def");
        map.put('4',"ghi");
        map.put('5',"jkl");
        map.put('6',"mno");
        map.put('7',"pqrs");
        map.put('8',"tuv");
        map.put('9',"wxyz");


        return map;
    }

    public static void main(String[] args){
           LetterComboofPhoneNum test = new LetterComboofPhoneNum();
           System.out.println(test.letterCombinations("23"));
        }

}
