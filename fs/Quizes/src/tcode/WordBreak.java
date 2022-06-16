package tcode;

import org.junit.Test;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public class WordBreak {
static HashSet<String>dict = new HashSet<>();
    //static List<String>dict = new LinkedList<>();

public boolean wordBreak(String s, List<String> wordDict) {

        if(s.length()==0)
            return true;

        for(int i = 1; i<=s.length(); ++i){
            String temp = s.substring(0,i);
            if( wordDict.contains(temp) && wordBreak(s.substring(i),wordDict)){
                return true;
            }

        }
        return false;

    }

    public boolean wordBreaks(String s, List<String> wordDict) {
       String tempt = s;
        for(int i = tempt.length()-1; i>=0; --i){
            String temp = tempt.substring(i);
           //System.out.println("temp before: "+temp);
            if( wordDict.contains(temp)){
                dict.add(temp);
                tempt = s.substring(0,i);
                System.out.println("temp: "+temp);
                System.out.println("tempt: "+tempt);
                if(wordDict.contains(tempt))
                    dict.add(tempt);
            }
        }


        return tempt.length()== 0;
    }

    public boolean wordBreakW(String s, List<String> dict) {
        if (s == null || s.length() == 0) return false;

        int n = s.length();

        boolean[] dp = new boolean[n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                String sub = s.substring(j, i + 1);

                if (dict.contains(sub) && (j == 0 || dp[j - 1])) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n - 1];
    }


    public static void main(String[] args){
        WordBreak test = new WordBreak();

        List<String> wordbreak = new ArrayList<>();
        wordbreak.add("cats");
        wordbreak.add("dog");
        wordbreak.add("sand");
        wordbreak.add("and");
        wordbreak.add("cat");
        System.out.println(test.wordBreak("catsandog",wordbreak));
        //test.wordBreaks("catsandog",wordbreak);
        //System.out.println(dict);
        System.out.println(test.wordBreaks("catsandog",wordbreak));
        System.out.println(dict);
    }

    @Test
    public void testUno(){
        WordBreak test = new WordBreak();

        List<String> wordbreak = new ArrayList<>();
        wordbreak.add("leet");
        wordbreak.add("code");
        System.out.println(test.wordBreaks("tcode",wordbreak));
       // test.wordBreaks("leetcode",wordbreak);
        System.out.println(dict);

    }
    @Test
    public void testDos(){
        WordBreak test = new WordBreak();

        List<String> wordbreak = new ArrayList<>();
        wordbreak.add("apple");
        wordbreak.add("pen");
        System.out.println(test.wordBreaks("applepenapple",wordbreak));
        test.wordBreaks("applepenapple",wordbreak);
        System.out.println(dict);

    }
    @Test
    public void testTre(){
        WordBreak test = new WordBreak();

        List<String> wordbreak = new ArrayList<>();
        wordbreak.add("a");
        wordbreak.add("b");
        wordbreak.add("bbb");
        wordbreak.add("bbbb");
        System.out.println(test.wordBreaks("bb",wordbreak));

        System.out.println(dict);

    }

    @Test
    public void testFour(){
        WordBreak test = new WordBreak();

        List<String> wordbreak = new ArrayList<>();

        wordbreak.add("bbb");
        wordbreak.add("bbbb");
        System.out.println(test.wordBreaks("bbbbbbb",wordbreak));

        System.out.println(dict);

    }
}
