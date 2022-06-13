package il.co.ilrd.misc;

import java.util.Collections;
import java.util.HashMap;

public class AudioCodes {
    static final HashMap<String, Double> prices = new HashMap<>();
    static final HashMap<Long, Double> priceMap = new HashMap<>();
    public static double getPrice(String phonenumber){
        String biggestPrefix = Collections.max(prices.keySet());
        int longestPrefix = biggestPrefix.length();
        for(int i = longestPrefix;i>0;--i){
            Double price = prices.get(phonenumber.substring(0,i));
            if(price != null)
                return price;
        }
        return 0.5;
    }
    public static double getPrice(Long phonenumber){

        int longestPrefix = maxDigits();
        int phoneDigits = maxDigits(phonenumber);
        phonenumber = cutNumber(phonenumber,phoneDigits - longestPrefix);

        for(int i = longestPrefix;i>0;--i){
            Double price = priceMap.get(phonenumber);
            if(price != null)
                return price;
            phonenumber/=10;
        }
        return 0.5;
    }

    private static long cutNumber(Long number, int howMuch){
        while(howMuch>0){
            number/=10;
            --howMuch;
        }
        return number;
    }
    private static int maxDigits(){
        Long biggest = Collections.max(priceMap.keySet());
        int counter = 0;
        while(biggest !=0){
            biggest /=10;
            ++counter;
        }
        return counter;
    }
    private static int maxDigits(Long number){
        int counter = 0;
        long temp = number;
        while(temp !=0){
            temp /=10;
            ++counter;
        }
        return counter;
    }
    private static void initBook(){
        prices.put("43660", 0.377);
        prices.put("4367", 0.79);
        prices.put("43710", 0.61);
        prices.put("431", 0.117);
        prices.put("43", 0.218);

        priceMap.put(43660L,0.377);
        priceMap.put(4367L,0.79);
        priceMap.put(43710L,0.61);
        priceMap.put(431L,0.117);
        priceMap.put(43L,0.218);

    }
    public static void main(String[] args){
        initBook();

        // System.out.println(prices.values());
        // System.out.println("mac digits: "+ maxDigits());
        System.out.println(getPrice("436601"));
        System.out.println(getPrice("4367314"));
        System.out.println(getPrice("43710123"));
        System.out.println(getPrice("431542"));
        System.out.println(getPrice("4345845"));
        System.out.println(getPrice("44123"));
        System.out.println("with other::");
        System.out.println(getPrice(436601L));
        System.out.println(getPrice(4367314L));
        System.out.println(getPrice(43710123L));
        System.out.println(getPrice(431542L));
        System.out.println(getPrice(4345845L));
        System.out.println(getPrice(44123L));
    }


}
