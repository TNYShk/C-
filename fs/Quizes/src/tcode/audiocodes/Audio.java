package tcode.audiocodes;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.*;

public class Audio {
    private static Node root;
    static Node[] list;

    static Map<Integer,String> parentMap = new LinkedHashMap<>();
    public Audio(){
        list = new Node[7];
        root = new Node();

        list[0] = new Node();
        list[1] = new Node(114,root,"Topology View");
        list[2] = new Node(115,root,"CORE ENTITIES");
        list[3] = new Node(116,list[2],"SRDs");
        list[4] = new Node(117,list[2], "SIP Interfaces");
        list[5] = new Node(122,root,"CODERS & PROFILES");
        list[6] = new Node(124,list[5],"IP Profiles");
    }

public static void hashMapJSON() throws IOException {
    URL url = new URL("http://www.mocky.io/v2/5c3c7ad13100007400a1a401");

    HttpURLConnection http = (HttpURLConnection)url.openConnection();
    http.setRequestProperty("Accept", "application/json");
    http.setUseCaches(false);
    http.setDoOutput(false);

    try( InputStream inputStream = http.getInputStream();
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
    public void printAll(){
        System.out.print("root:    ");
        System.out.println("\t children: "+getChildren(0));
           for(Integer id: parentMap.keySet()){
                   System.out.print("node: " +id);
                   System.out.println("\t children: "+getChildren(id));


           }
    }
    public void printOnlyFertile(){
        System.out.print("root:    ");
        System.out.println("\t children: "+getChildren(0));

        for(Integer id: parentMap.keySet()){

            if(!getChildren(id).isEmpty()){
                System.out.println("node: " +id);
                System.out.println("\t children: "+getChildren(id));
            }

        }
    }
    public void printbyLevel() {
       List<Integer> level = getChildren(0);
       System.out.println(level);
       for(Integer l: level){
           if(!getChildren(l).isEmpty())
            System.out.print("   "+getChildren(l));
       }
       System.out.println();
       StringBuilder dash = new StringBuilder();
       for(Integer id: parentMap.keySet())
           if(!level.contains(id)){
               if(!getChildren(id).isEmpty())
                    System.out.print(dash+""+getChildren(id));
           }else{ dash.append("     ");}
    }



 private static class Node{
        private int id;
        private Node parent;
        private String text;

        private Node(){
            id = 0;
            parent = null;
            text = "root";
        }
        public Node(int id, Node parent, String text){
            this.id = id;
            this.parent = parent;
            this.text = text;
        }

    }



  //  Israeli ID numbers have a checksum digit.
// The algorithm is:
//             ID number    0  4  2  6  1  9  7  9
//             multiply by  1  2  1  2  1  2  1  2
//             result       0  8  2  12 1  18 7  18
//       sum of all digits  0+8+2+1+2+1+1+8+7+1+8 = 39
//   complement to next ten 40-39 = 1
// So the full ID number would be 042619791.

    // Try it with your own ID number, make sure you understand the algorithm.
// Write a function to perform the checksum digit calculation,

    public int ChecksumDigit(int ID_number){
        int mod;
       boolean flag = true;
       int result = 0;

        while(ID_number>0){
            mod = ID_number%10;
            if(flag){
                result += innerSum(mod *2);
                flag = false;
            }else{
                result += innerSum(mod);
                flag = true;
            }
            ID_number /=10;
        }
       return (result%10 == 0)? 0: 10 - result%10;

    }
    public int innerSum(int tempRes){
        int res = 0;
        if(tempRes>9) {
            res += tempRes % 10;
            res += tempRes / 10;

            return res;
        }
        return tempRes;
    }



    public static void main(String[] args) throws IOException {
        Audio test = new Audio();
        System.out.println(test.ChecksumDigit(30413436));

        hashMapJSON();
      /* System.out.println("get specific node's children: ");
        System.out.println("parent 115: "+test.getChildren(115));
        System.out.println("\n\tprint only fertile nodes: ");*/
        //test.printOnlyFertile();
   /*     System.out.println("\n\tprint all: ");
        test.printAll();*/

        test.printbyLevel();



    }
}
