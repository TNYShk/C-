package datastructures;

import java.util.Set;
import java.util.TreeMap;

public class TreeMapp {
     TreeMap<Integer,String> intStrMap;
    TreeMap<String,String> strStrMap;


    public void makeIntStrTree(){
        intStrMap = new TreeMap<>();

        intStrMap.put(2,"b");
        intStrMap.put(5,"e");
        intStrMap.put(4,"d");
        intStrMap.put(26,"z");
        intStrMap.put(25,"y");
        intStrMap.put(24,"x");
        intStrMap.put(23,"w");
        intStrMap.put(22,"v");
        intStrMap.put(21,"u");
        intStrMap.put(14,"n");
        intStrMap.put(1,"a");
        intStrMap.put(20,"t");

        Integer highestKey = intStrMap.lastKey();
        Integer lowest = intStrMap.firstKey();
        System.out.println("lowest key: "+ lowest+ " highest: "+ highestKey);
        System.out.println(intStrMap.values());
        System.out.println(intStrMap.keySet());
        intStrMap.merge(26,"z",String::concat);
        System.out.println(intStrMap.get(26));

        Set<Integer> smaller5Keys = intStrMap.headMap(5).keySet();
        Set<Integer> biggerKeys = intStrMap.tailMap(5).keySet();
        System.out.println(smaller5Keys);

    }

    public void makeStrStrTree(){
        strStrMap = new TreeMap<>();
    }

    public static void main(String[] args){
        TreeMapp test = new TreeMapp();
        test.makeIntStrTree();
    }
}
