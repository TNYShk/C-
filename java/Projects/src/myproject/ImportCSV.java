package myproject;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.text.ParseException;
import java.time.LocalDate;
import java.util.*;

public class ImportCSV {
    private static String[] headers;
    protected List<Row> data;
    protected Path pathToFile;

    public ImportCSV(String filename) throws NoSuchFileException {
        data = new LinkedList<>();
        pathToFile = Paths.get(filename);
        if(!Files.exists(pathToFile)){
            throw new NoSuchFileException("No such File");
        }
    }
    public static List<Row> readFromCSV(List<Row> mydata, Path path) throws IOException {
        try(BufferedReader br = Files.newBufferedReader(path, StandardCharsets.UTF_8)){
            String line = br.readLine();
            headers = line.split(",");
            int columns = headers.length;
            line = br.readLine();
            while(line != null) {

                String[] attributes = line.split(",");
                List<String> splitter = Arrays.asList(attributes);
                Row row = createRow(splitter, columns);
                mydata.add(row);
                line = br.readLine();
            }
        }
        Collections.sort(mydata);
        return mydata;
    }

    private static Row createRow(List<String> metadata, int columns) {
        int cap = Integer.parseInt(metadata.get(0).trim());
        int price = Integer.parseInt(metadata.get(1).trim());

        LocalDate start = java.time.LocalDate.parse(metadata.get(2).trim());
        LocalDate end = ((metadata.size() != columns))? (java.time.LocalDate.now()) : java.time.LocalDate.parse(metadata.get(3).trim());

        return new Row(cap,price,start,end);
    }

    public static void printMeta(String[] headers){
        for(String e: headers){
            System.out.print(e+ " ");
        }
        System.out.println();
    }

    public static void sortList(List<Row> list){
        Collections.sort(list);
    }


    public static void main(String[] args) throws IOException, ParseException {
        System.out.println(Path.of("rent_data.csv").toAbsolutePath());

        ImportCSV test = new ImportCSV("/Users/tanyashkolnik/git/java/Projects/src/myproject/rent_data.csv");
        //ImportCSV test = new ImportCSV(Path.of("rent_data.csv").toAbsolutePath().toString());
        //readFromCSV(test.data,test.pathToFile);
        //printMeta(headers);
        //System.out.print("\n"+test.data);


    }


}
