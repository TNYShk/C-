package leetcode;

import java.util.HashMap;

public class FractionToDecimal {

    public String fractionToDecimal(int numer, int denom) {
        HashMap<Long, Integer> fractMap = new HashMap<>();
        StringBuilder answer = new StringBuilder();
        long numerator = numer;
        long denominator = denom;

        if(numerator * denominator < 0){
            answer.append("-");
            numerator = Math.abs(numerator);
            denominator = Math.abs(denominator);
        }

        long remainder = numerator % denominator;

        answer.append(numerator / denominator);
        remainder %= denominator;

        if (remainder == 0) {
            return answer.toString();
        }
        answer.append(".");
        fractMap.put(remainder, answer.length());

        while (remainder != 0) {
            remainder *= 10;
            answer.append(remainder / denominator);
            remainder %= denominator;

            if (fractMap.containsKey(remainder)) {
                int idx = fractMap.get(remainder);
                answer.insert(idx, "(");
               return String.valueOf(answer.append(")"));
            } else {
                fractMap.put(remainder, answer.length());
            }
        }
        System.out.println(fractMap.entrySet());
        return answer.toString();
    }

    public static void main(String[] args){
        FractionToDecimal test = new FractionToDecimal();
        System.out.println(test.fractionToDecimal(1,2));
        System.out.println(test.fractionToDecimal(4,333));
        System.out.println(test.fractionToDecimal(2,1));
        System.out.println(test.fractionToDecimal(1,6));
        System.out.println(test.fractionToDecimal(-50,8));
        //System.out.println(test.fractionToDecimal(-1,-2147483648));

    }

}
