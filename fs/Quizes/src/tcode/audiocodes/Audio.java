package tcode.audiocodes;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.*;

public class Audio {
    private static Node root;
    static Node[] list;
    static LinkedHashMap<Node,List<Node>> map = new LinkedHashMap<>();

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

public static void test() throws IOException {
    URL url = new URL("http://www.mocky.io/v2/5c3c7ad13100007400a1a401");
    HttpURLConnection http = (HttpURLConnection)url.openConnection();
    http.setRequestProperty("Accept", "application/json");
http.connect();


    Map<String, List<String>> fieldMap = new HashMap<>();
    System.out.println(http.getResponseCode() + " " + http.getResponseMessage());

    System.out.println(http.getContent());
    fieldMap = http.getHeaderFields();

    System.out.println(fieldMap);
    http.disconnect();

}

    public static void constructTree(){
        LinkedHashSet<Node> parents = new LinkedHashSet<>();
          for(int i =1;i< list.length;++i)
              parents.add(list[i].parent);
    for(Node n: parents)
          System.out.print (n.id + " ,");

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
            this.id= id;
            this.parent = parent;
            this.text = text;
        }

    }
/*
  root(id:0, parent:null,text);

    children[]nodes
            (id: ,parent: , text:...)
        example:
            (114,0,topologyviw)
            (115,0, core entities)

            (122,0, coders & profilers)
            (119,115, srdx)

          0
    114   115  122
          119  123 124
*/


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
    Audio tttt = new Audio();
    System.out.println(tttt.ChecksumDigit(30413436));
    /*Node[] list = new Node[6];
    list[0] = tttt.root;
    list[1] = new Node(114,root,"Topology View");
    list[2] = new Node(115,root,"CORE ENTITIES");
    list[3] = new Node(116,list[2],"SRDs");
    list[4] = new Node(117,list[2], "SIP Interfaces");
    list[5] = new Node(122,root,"CODERS & PROFILES");
    list[6] = new Node(124,list[5],"IP Profiles");*/

        constructTree();


        //test();


    }
}
