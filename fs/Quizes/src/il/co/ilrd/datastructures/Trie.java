package datastructures;

import java.util.ArrayList;
import java.util.HashMap;

public class Trie {
    private TrieNode root;
    private double[]rat = {0.377,0.79,0.61,0.117,0.218};

    public Trie(ArrayList<String> lost){
        root = new TrieNode();

        for(String w: lost){
            root.addWord(w);
        }
    }
    public Trie(String[] list){
        root = new TrieNode();
        int i =0;
        for(String w: list){
            root.addWord(w,rat[i]);
            ++i;
        }
    }
    public boolean contains(String prefix, boolean exact){
        TrieNode lastNode = root;
        int i = 0;
        for(i=0; i<prefix.length(); ++i){
            lastNode = lastNode.getChild(prefix.charAt(i));
            if(lastNode == null){
                return false;
            }
        }
        System.out.println(lastNode.rate);
        return !exact || lastNode.terminate();
    }

    public boolean contains(String predix){
        return contains(predix,false);
    }

    public TrieNode getRoot(){
        return root;
    }

    static class TrieNode {
        private HashMap<Character, TrieNode> children;
        private boolean terminator = false;
        private double rate = 0.5;
        private char charmer;

        public TrieNode() {
            children = new HashMap<>();
        }

        public TrieNode(char charmer) {
            this();
            this.charmer = charmer;
        }

        public char getChar() {
            return charmer;
        }

        public double getRate() {
            return rate;
        }

        public void addWord(String word) {
            if ((word == null) || word.isEmpty())
                return;

            char firstChar = word.charAt(0);

            TrieNode child = getChild(firstChar);
            if (child == null) {
                child = new TrieNode(firstChar);
                children.put(firstChar, child);
            }
            if (word.length() > 1) {
                child.addWord(word.substring(1));
            } else {
                child.setTerminate(true);
            }
        }

        public void addWord(String word, double rates) {
            if ((word == null) || word.isEmpty())
                return;

            char firstChar = word.charAt(0);

            TrieNode child = getChild(firstChar);
            if (child == null) {
                child = new TrieNode(firstChar);
                children.put(firstChar, child);
            }
            if (word.length() > 1) {
                child.addWord(word.substring(1), rates);
            } else {
                child.rate = rates;
                child.setTerminate(true);
            }
        }

        public TrieNode getChild(char cc) {
            return children.get(cc);
        }

        public boolean terminate() {
            return terminator;
        }

        public void setTerminate(boolean b) {
            terminator = b;
        }
    }
   public void getRate(String number){
        int longest = "43660".length();
        for(int i=longest;i>0;--i){
            if(contains(number.substring(0,i))){
                break;
            }
        }
   }

    public static void main(String[] args){
        String[] audio = {"43660","4367","43710","431","43"};
        Trie test = new Trie(audio);
        //System.out.println(test.contains("43660"));
        //System.out.println(test.contains("4367"));
        test.getRate("43710123");
        test.getRate("4345845");
        test.getRate("436601");
        test.getRate("4367314");
        test.getRate("44145");


    }
}
