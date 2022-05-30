package il.co.ilrd.varonis;

import java.io.*;
import java.nio.file.Files;
import java.util.*;

import static il.co.ilrd.varonis.Dictionary.*;

public class StringCounter {
    private LinkedList<Integer> list = new LinkedList<>();
    private static HashMap<String, Integer> dictionary;

    public StringCounter(LinkedList<Integer> list) {
        this.list = list;
    }

    public static void main(String[] args) throws IOException {

        dictionary = new HashMap<>();

        List<String> textFileList = Arrays.asList("/home/tanya/F1.txt");

        try {

            Dictionary reader = new Dictionary(dictionary);

            for (String text : textFileList) {
                reader.fileScanner(text);
            }

            Scanner textFile = new Scanner(new File("/home/tanya/F1.txt"));
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
        } finally {
            Vector<Integer> vec1 = new Vector<>(dictionary.values());
            //System.out.println(dictionary.values());
            //System.out.println(dictionary.keySet());
            //printDict(dictionary);
            //getMax(dictionary);
            /*List<Map.Entry<String, Integer>> words = new LinkedList<>();
            for (Map.Entry<String, Integer> entry :
                    dictionary.entrySet()) {
                words.add((Map.Entry<String, Integer>) dictionary.entrySet());
            }
*/
            produceOutput();
            printComma();
            //System.out.println(words);
/*
            FileWriter writing = new FileWriter("/home/tanya/F2.txt",true);
               // for(String word: dictionary.keySet()){

                    try (BufferedWriter writer = new BufferedWriter(writing)) {
                        for (Map.Entry<String, Integer> entry :
                                dictionary.entrySet()) {
                        writer.write(entry.getKey() + ": " + entry.getValue());
                        writer.newLine();
                    }
                }*/

        }
    }

    public static void produceOutput() throws IOException {

        FileWriter writing = new FileWriter("/home/tanya/F3.txt", true);
        // for(String word: dictionary.keySet()){

        try (BufferedWriter writer = new BufferedWriter(writing)) {
            for (Map.Entry<String, Integer> entry :
                    dictionary.entrySet()) {
                writer.write(entry.getKey() + ": " + entry.getValue());
                writer.newLine();
            }
        }
    }

    public static void printComma() throws IOException {
        FileWriter writing = new FileWriter("/home/tanya/F4.txt", true);
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



