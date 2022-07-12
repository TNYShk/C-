package il.co.ilrd.misc.varonis;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Dictionary {
//Varonis
private static Map<String, Integer> dictionary;

    public Dictionary(Map<String, Integer> dictionary) {
        Dictionary.dictionary = dictionary;
    }
    private Dictionary(){
        dictionary = new LinkedHashMap<>();
    }

    public void fileScanner(String textFileName) {
        try {

            Scanner textFile = new Scanner(new File(textFileName));

            while (textFile.hasNext()) {
                dictionary.merge(textFile.next().toLowerCase().trim(),1,Integer::sum);
            }

            textFile.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
    public static Map<String, Integer> getDictionary(){
        return dictionary;
    }
    public static void printDict(HashMap<String, Integer> dictionary) {
        System.out.println(dictionary.keySet());

    }
    public static Integer getMax() {
        int max = Collections.max(dictionary.values());
        return max;
    }
    }

