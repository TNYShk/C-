package il.co.ilrd.misc;

import org.junit.Assert;

import java.util.ArrayList;
import java.util.HashMap;

public class Cobwebs {
    static final ArrayList<String> week = new ArrayList<>();
    static final HashMap<Character,Integer> romanMap = new HashMap<>();
    private void initWeek(){
        week.add("sun");
        week.add("mon");
        week.add("tue");
        week.add("wed");
        week.add("thu");
        week.add("fri");
        week.add("sat");
    }
    public String getDay(String day, int num){
        int idx = week.indexOf(day);
        if(idx == -1)
            return "bad input try again!";
        int calc = num + idx;
        calc %=7;

        return week.get(calc);
    }
    private static void initMap(){
        romanMap.put('I', 1);
        romanMap.put('V', 5);
        romanMap.put('X', 10);
        romanMap.put('L', 50);
        romanMap.put('C', 100);
        romanMap.put('D', 500);
        romanMap.put('M', 1000);
    }
    public static int romanToInt(String roman) {
        if (roman == null || roman.length() == 0){
            System.out.println("bad input!");
            return -1;
        }
        roman = roman.toUpperCase();
        initMap();

        int result = romanMap.get(roman.charAt(roman.length() - 1));

        for(int i = 0; i < roman.length() - 1; ++i){
            if(romanMap.get(roman.charAt(i)) < romanMap.get(roman.charAt(i + 1))) {
                result -= romanMap.get(roman.charAt(i));
            }else{
                result += romanMap.get(roman.charAt(i));
            }
        }

        return result;
    }

    public static void main(String[] args){
        System.out.println("hello world");
        Cobwebs test = new Cobwebs();
        test.initWeek();
        System.out.println(test.getDay("sun",365));
        System.out.println(test.getDay("fri",0));
        System.out.println(test.getDay("sat",1));
        System.out.println(test.getDay("fri",3));
        System.out.println("\nroman to ints:");
        Assert.assertEquals(1934,romanToInt("MCMXXXIV"));
        System.out.println(romanToInt("MCMXXXIV"));
        Assert.assertEquals(1934,romanToInt("mcmxxxiv"));
        System.out.println(romanToInt("mcmxxxiv"));
        System.out.println(romanToInt("mcmi"));
        Assert.assertEquals(1901,romanToInt("mcmi"));
        System.out.println(romanToInt("xxxiv"));
        Assert.assertEquals(34,romanToInt("xxxiv"));
        System.out.println(romanToInt("c"));
        Assert.assertEquals(205,romanToInt("ccv"));
        System.out.println(romanToInt("x"));
        System.out.println(romanToInt("i"));
    }
}
