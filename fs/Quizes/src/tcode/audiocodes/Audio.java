package tcode.audiocodes;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.*;

public class Audio {
    static Map<Integer, String> parentMap = new LinkedHashMap<>();

    public static void hashMapJSON() throws IOException {
        URL url = new URL("http://www.mocky.io/v2/5c3c7ad13100007400a1a401");

        HttpURLConnection http = (HttpURLConnection) url.openConnection();
        http.setRequestProperty("Accept", "application/json");
        http.setUseCaches(false);
        http.setDoOutput(false);

        try (InputStream inputStream = http.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream))) {

            List<String> response = new ArrayList<>();

            String line = "";
            while ((line = reader.readLine()) != null) {
                response.add(line);
            }
            reader.close();

            for (int i = 3; i < response.size() - 13; i += 13) {
                Integer id = Integer.parseInt(response.get(i).substring(18, 21));
                parentMap.put(id, response.get(i + 1).substring(22));
            }
        }
        http.disconnect();
    }

    public List<Integer> getChildren(int parent) {
        List<Integer> children = new LinkedList<>();

        for (Map.Entry<java.lang.Integer, java.lang.String> entry : parentMap.entrySet()) {
            if (entry.getValue().contains(String.valueOf(parent)))
                children.add(entry.getKey());
        }
        return children;
    }

    public void printAll() {
        System.out.print("root  ");
        System.out.println("\t children: " + getChildren(0));
        for (Integer id : parentMap.keySet()) {
            System.out.print("node: " + id);
            System.out.println("\t children: " + getChildren(id));
        }
    }

    public void printOnlyFertile() {
        System.out.print("root:    ");
        System.out.println("\t children: " + getChildren(0));

        for (Integer id : parentMap.keySet()) {

            if (!getChildren(id).isEmpty()) {
                System.out.println("node: " + id);
                System.out.println("\t children: " + getChildren(id));
            }
        }
    }

    public void printbyLevel() {
        List<Integer> level = getChildren(0);
        System.out.println(level);
        for (Integer l : level) {
            if (!getChildren(l).isEmpty())
                System.out.print("   " + getChildren(l));
        }
        System.out.println();
        StringBuilder dash = new StringBuilder();
        for (Integer id : parentMap.keySet())
            if (!level.contains(id)) {
                if (!getChildren(id).isEmpty())
                    System.out.print(dash + "" + getChildren(id));
            } else {
                dash.append("     ");
            }
    }

    public static void main(String[] args) throws IOException {
        Audio test = new Audio();

        hashMapJSON();
        System.out.println("get specific node's children: ");
        System.out.println("parent 115: " + test.getChildren(115));

        System.out.println("\n\tprint only fertile nodes: ");
        test.printOnlyFertile();

        System.out.println("\n\tprint all: ");
        test.printAll();

        System.out.println("\n\tprint by LEVEL");
        test.printbyLevel();

    }
}
