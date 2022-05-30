package il.co.ilrd.varonis;

import java.io.*;
import java.nio.file.Files;
import java.util.*;

import static il.co.ilrd.varonis.Dictionary.*;

public class StringCounter {
    private LinkedList<Integer> list = new LinkedList<>();
    private static HashMap<String, Integer> dictionary;
    private static String path;
    public StringCounter(String files) {
        dictionary = new HashMap<>();
        path = files;

    }
    public static void work(){
        List<String> textFileList = Arrays.asList(path);
        try {

            Dictionary reader = new Dictionary(dictionary);

            for (String text : textFileList) {
                reader.fileScanner(text);
            }

            Scanner textFile = new Scanner(new File(path));
            ArrayList<String> file = new ArrayList<>();

            while (textFile.hasNext()) {
                file.add(textFile.next().trim().toLowerCase());
            }

            for (String word : file) {
                dictionary.merge(word, 1, Integer::sum);
                Integer dict = dictionary.get(word);
                // dictionary.merge(word,1,Integer::sum);

            }
            textFile.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
    }
    }

    public static void produceOutput() throws IOException {

        FileWriter writing = new FileWriter("/Users/tanyashkolnik/Documents/F3.txt", false);
        // for(String word: dictionary.keySet()){

        try (BufferedWriter writer = new BufferedWriter(writing)) {
            for (Map.Entry<String, Integer> entry :
                    dictionary.entrySet()) {
                writer.write(entry.getKey() + ": " + entry.getValue());
                writer.newLine();
            }
        }
    }
    public static void maxWord(){
        Integer max = Dictionary.getMax();
        for (Map.Entry<String, Integer> entry : dictionary.entrySet()) {
            if(entry.getValue().equals(max))
                System.out.println(entry.getKey()+ ": "+ entry.getValue());
        }
    }

    public static void printComma() throws IOException {
        FileWriter writing = new FileWriter("/Users/tanyashkolnik/Documents/F4.txt", false);
        List<String> sorted = new ArrayList<>(dictionary.keySet());
        List<Map.Entry<String,Integer>> mix = new ArrayList<>();

        Collections.sort(sorted);

        try (BufferedWriter writer = new BufferedWriter(writing)) {
            for (String w : sorted) {
                writer.write(w);
                writer.write(",");
              //  writer.newLine();
            }

        }

    }
}



