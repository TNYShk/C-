package il.co.ilrd.varonis;

import java.io.File;
import java.io.FileNotFoundException;
import java.nio.file.Files;
import java.util.Collections;
import java.util.HashMap;
import java.util.Scanner;

public class Dictionary<K,V> {

        private static HashMap<String, Integer> dictionary = new HashMap<>();

        public Dictionary(HashMap<String, Integer> dictionary) {
            this.dictionary = dictionary;
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

        public static void printDict(HashMap<String, Integer> dictionary) {
            System.out.println(dictionary.keySet());

        }
    public static Integer getMax() {
        int max = Collections.max(dictionary.values());

            return max;
        }


    }

