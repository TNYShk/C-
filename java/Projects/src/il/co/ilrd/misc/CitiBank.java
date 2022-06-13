package il.co.ilrd.misc;



import java.util.*;

class CitiBank {
    public static void main(String[] args) {

        // part one
        System.out.println(isPermutation("hello", "lloeh")); // should be true
        System.out.println(isPermutation("hello", "bye")); // should be false
        // part two
        List<String> strings = new LinkedList<>();
        strings.add("hello");
        strings.add("lloeh");
        strings.add("bye");
        strings.add("hi");
        strings.add("eby");
        strings.add("ebyy");
        strings.add("");
        System.out.println(sortPermutations(strings));
        System.out.println(sortPermutation(strings));

    }

    public static boolean isPermutation(String first, String second) {
        if(first.length() == second.length()) {
            Map<Character, Integer> letterMap = initMap(first);

            for (int i = 0; i < second.length(); ++i) {
                letterMap.merge(second.charAt(i), -1,Integer:: sum);
            }
            return Collections.max(letterMap.values()) == 0 && (Collections.min(letterMap.values()) == 0);
        }
        return false;
    }
    public static Map<Character,Integer> initMap(String first){
        Map<Character, Integer> letterMap = new HashMap<>();
        for (int i = 0; i < first.length(); ++i) {
            letterMap.merge(first.charAt(i), 1, Integer::sum);
        }
        return letterMap;
    }

    static  List<List<String>> wordHotel = new ArrayList<>();
    public static List<List<String>> sortPermutations(List<String> strings) {

        for(int i = 0; i< strings.size();++i){
           for (int j = 0; (j < wordHotel.size()); ++j) {
               if(isPermutation(strings.get(i), wordHotel.get(j).get(0))) {
                   wordHotel.get(j).add(strings.get(i));
                   strings.remove(i);
                   break;
               }
           }
           List<String> floor = new ArrayList<>();
           floor.add(strings.get(i));
           wordHotel.add(floor);
       }
        return wordHotel;
    }

    public static Collection<Set<String>> sortPermutation(List<String> strings) {
        Map<Map<Character,Integer>,Set<String>> megaList = new HashMap<>();

        for (String string : strings) {
            Set<String> list = new HashSet<>();
            list.add(string);
            if(megaList.containsKey(list)){
                megaList.get(initMap(string)).add(String.valueOf(list));
            }else
            megaList.put((initMap(string)), list);
        }

        return megaList.values();
    }
}