package il.co.ilrd.varonis;

import il.co.ilrd.hashMap.HashMap;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class FileTrack<K,V> {
static ArrayList<LinkedList<String>> maps;
    //private static HashSet<String> dictionary = new HashSet<>();
    static Map<String, Integer> dictionary = new HashMap<>();
    //public static Map<String,Integer> map = new java.util.HashMap<>();
    public static Path realPath;
    static String path;
    public FileTrack(String path) throws IOException {

        realPath = Paths.get(path);
        this.path = path;
        if(!Files.exists(realPath)) {
            throw new NoSuchFileException("no file");
        }
        List<String> counter = Files.readAllLines(realPath);

        System.out.println(counter.size());


        //Files.copy(realPath,Paths.get("/home/tanya/F2.txt"));

    }

public static void read(String files) throws IOException {
    File file = new File(files);
    FileInputStream fn = new FileInputStream(file);
    InputStreamReader input = new InputStreamReader(fn);
    BufferedReader reader = new BufferedReader(input);
    String sentence;
    int counter =0;
    if((sentence= reader.readLine()) != null) {
        String[] wordlist = sentence.split(" ");
        dictionary.merge(String.valueOf(wordlist),1,Integer::sum);
        dictionary.put(String.valueOf(wordlist),counter);

    }
}








    public static void main(String[]args) throws IOException {
        FileTrack test = new FileTrack("/home/tanya/F1.txt");
        read("/home/tanya/F1.txt");
        System.out.println(dictionary.values());


    // dictionary.contains("Help");

        }
    }

