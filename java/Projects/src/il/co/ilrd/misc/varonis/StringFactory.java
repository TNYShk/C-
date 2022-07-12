package il.co.ilrd.misc.varonis;

import java.io.*;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

//Varonis
public class StringFactory {
    private final HashMap<String,Operation> operMap;
    private Map<String, Integer> dictionary;
    private static String path;
    private  FileWriter writing;


    public StringFactory(String file) throws IOException {
        dictionary = new LinkedHashMap<>();
        operMap = new HashMap<>();
        path = file;
        Path currentRelativePath = Paths.get("");
        String path = currentRelativePath.toAbsolutePath().toString();
        path = path.concat("/FactoryOutput.txt");
        writing = new FileWriter(path, false);
        operMap.put("sort -d",sortDesc);
        operMap.put("sort -a",this::sortAsc);
        operMap.put("count", this::produceOutput);
        operMap.put("by", this::maxWord);

    }
    public void initDictionary(){
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
            }
            textFile.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void operate(String str) throws IOException {
        operMap.get(str).operate();
    }
    interface Operation{
        void operate() throws IOException;
    }

    public void produceOutput() throws IOException {
        Path currentRelativePath = Paths.get("");
        String path = currentRelativePath.toAbsolutePath().toString();
        path = path.concat("/wordCounter.txt");
        FileWriter writing = new FileWriter(path, false);
        try (BufferedWriter writer = new BufferedWriter(writing)) {
            for (Map.Entry<String, Integer> entry : dictionary.entrySet()) {
                writer.write(entry.getKey() + " : " + entry.getValue());
                writer.newLine();
            }
        }
        System.out.println("created output file in working directory with the desired sort");
    }
    public void maxWord(){
        Integer max = Dictionary.getMax();
        for (Map.Entry<String, Integer> entry : dictionary.entrySet()) {
            if(entry.getValue().equals(max)) {
                System.out.println("most common word is");
                System.out.println(entry.getKey() + ": " + entry.getValue());
            }
        }
    }
    public  void sortAsc() throws IOException {
        List<String> sorted = new ArrayList<>(dictionary.keySet());
        Collections.sort(sorted);
        try (BufferedWriter writer = new BufferedWriter(writing)) {
            for (String w : sorted) {
                writer.write(w);
                writer.newLine();
            }

        }
        System.out.println("created output file in working directory with the desired sort");
    }
    Operation sortDesc = () -> {
        List<String> sorted = new ArrayList<>(dictionary.keySet());

        Collections.sort(sorted);
        Collections.reverse(sorted);
        try (BufferedWriter writer = new BufferedWriter(writing)) {
            for (String w : sorted) {
                writer.write(w);
                writer.newLine();
            }

        }
        System.out.println("created output file in working directory with the desired sort");
    };
    public void printSplit(String some) throws IOException {
        List<String> sorted = new ArrayList<>(dictionary.keySet());

        Collections.sort(sorted);
        if(some.equals("-c"))
            some = ",";
        if(some.equals("-s"))
            some = " ";
        if(some.equals("-n"))
            some = "  ";

        realPrint(sorted,some);

    }

    private void realPrint(List<String> sorted, String some) throws IOException {

        try (BufferedWriter writer = new BufferedWriter(writing)) {
            for (String w : sorted) {
                writer.write(w);
                writer.write(some);
                if(some.equals("  "))
                    writer.newLine();
            }
        }
        System.out.println("created output file in working directory with the "+ some);
    }

}



