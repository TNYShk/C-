package tcode.audiocodes;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;


import java.io.*;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class TreeNode<T> {
    private final int id;
    private final T data;
    private List<TreeNode<T>> children;

    private TreeNode<T> parent;
    private int depth;

    public TreeNode(int id, T data){
        this(id,data,null);
    }

    public TreeNode(int id, T data, TreeNode parent){
        children = new LinkedList<>();
        this.id = id;
        this.data = data;
        this.parent = parent;
        this.depth =(parent == null)?0: parent.getDepth()+1;
        if(parent != null)
            parent.addChild(this);
    }

    public int getDepth(){
        return this.depth;
    }

    public void addChild(int id, T data){
        TreeNode<T> newChild = new TreeNode<>(id,data);
        this.addChild(newChild);
    }
    public void addChild(TreeNode<T> child){
        this.children.add(child);
    }


    private void setParent(TreeNode<T> parent){
        this.setDepth(parent.getDepth() +1);
        parent.addChild(this);
        this.parent = parent;
    }
    public void setDepth(int level){
        this.depth = level;
    }

    public TreeNode<T> getParent(){
        return parent;
    }

    public List<TreeNode<T>> getChildren(){
       //children.sort(Comparator.comparingInt(a -> (a).id));
        children.sort(Comparator.comparingInt(a -> (a).parent.id)); //sort by parent id
        return children;
    }

    public T getText(){
        return data;
    }

    @Override
    public String toString() {
        String out = "";
        out += "Node: "+this.id +" "+ this.getText().toString()  + " | Parent: " + (this.getParent() == null ? "None" : this.parent.id) +
                " | Children: " + (this.getChildren().size() == 0 ? "None" : "");
        for(TreeNode<T> child : this.getChildren()) {
            out += "\n\t"+dashMaker(this.getDepth()) +"id: " +child.id+ " | data: " + child.getText().toString() +
                    " | Parent: " + (child.getParent() == null ? "None" : child.getParent().id);
        }
        return out;
    }

    private StringBuilder dashMaker(int depth){
        StringBuilder dash = new StringBuilder();

        while(--depth>0){
            dash.append(" ");
        }

        return dash;

    }
    private static String readAll(Reader rd) throws IOException {
        StringBuilder sb = new StringBuilder();
        int cp;
        while ((cp = rd.read()) != -1) {
            sb.append((char) cp);
        }
        return sb.toString();
    }

    public static JSONObject readJsonFromUrl(String url) throws IOException, JSONException {
        InputStream is = new URL(url).openStream();
        try {
            BufferedReader rd = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));
            String jsonText = readAll(rd);

            return new JSONObject(jsonText);
        } finally {
            is.close();
        }
    }
    public void workIt(String[] str){
        int[]parents = new int[str.length];
        int[]ids = new int[str.length];
        String[]texts = new String[str.length];

        for(int i=0;i< str.length;++i){
            int id = str[i].indexOf("parent");
            String ss = str[i].substring(id+8,id+11);
            parents[i] = (ss.contains("0")? 0: Integer.parseInt(ss));

        }

        for(int i=0;i< str.length;++i){
            int id = str[i].indexOf("id");
            String ss = str[i].substring(id+4,id+7);
           if(checkNum(ss))
                ids[i] =  Integer.parseInt(ss);

        }
        for(int i=0;i< str.length;++i){
            int id = str[i].indexOf("text");
            int textEnd = str[i].indexOf("href");
            texts[i] = str[i].substring(id+6,textEnd-1);
        }

        for(int i =0;i<str.length;++i){
           addChild(new TreeNode(ids[i],texts[i], new TreeNode(parents[i], " ")));
        }
    }
    private static boolean checkNum(String s){

        for(int i =0;i<s.length();++i){
            if(!Character.isDigit(s.charAt(i))){
                return false;
            }
        }
        return true;
    }


    public static void main(String[] args) throws IOException {
        TreeNode<String> root = new TreeNode<>(0, "root");
/*
        TreeNode<String> o5 = new TreeNode(122, "CODERS & PROFILES",root);
        TreeNode<String> o1 = new TreeNode(114, "Topology View",root);
        TreeNode<String> o2 = new TreeNode(115, "CORE ENTITIES",root);
        TreeNode<String> o3 = new TreeNode(116, "SRDs", o2);
        TreeNode<String> o4 = new TreeNode(117, "SIP Interfaces", o2);
        TreeNode<String> o7 = new TreeNode(118, "Media Realmss", o2);
        TreeNode<String> o6 = new TreeNode(124, "IP Profiles");
        o6.setParent(o5);
        System.out.println("manual insertion of nodes example");
        //manual insertion of nodes:
        System.out.println(root);*/

        System.out.println("\n\tJSON library own parsing version!");
        JSONObject json = readJsonFromUrl("http://www.mocky.io/v2/5c3c7ad13100007400a1a401");
        JSONArray arr = json.getJSONArray("nodes");
        String[]nodes = new String[arr.length()];
        for(int i=0;i<arr.length();++i){
            nodes[i] = arr.getJSONObject(i).toString();
        }
        root.workIt(nodes);
        TreeNode<String> someChild = root.children.get(5);
        System.out.println(someChild.id);
        //System.out.println(someChild);
        //parsed JSON version
        System.out.println(root);



  }




}
