package tcode;
//given an integer, print its string value in english -> 123 one hundred and twenty-three.
public class EngInt {
    private String[]smalls = {"zero","one","two","three","four","five","six","seven","eight","nine","ten",
            "eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
    private String[]tens = {"","","twenty","thirty","fourty","fifty","sixty","seventy","eighty","ninety"};

    private String[]bigs = {"","thousand","million","billion"};
    private String negative = "minus";


    public String convert(int num){
        StringBuilder ans = new StringBuilder();
        boolean biggg = false;
        boolean negat = false;
        if(num == 0)
            return ans.append(smalls[0]).toString();
        if(num<0) {
           negat = true;
            num *=-1;
        }
        int chunkCount = 0;
        while(num >0){
            if(num%1000 !=0){
                biggg = true;
               ans.append(convertChunk(num%1000)+ bigs[chunkCount]);

            }
            num /=1000;
            ++chunkCount;
        }
        if(biggg){
            String big = ans.substring(ans.indexOf(","),ans.length());
            String mingle = ans.substring(0,ans.indexOf(","));
            String finit = big + mingle;
            finit = finit.substring(finit.indexOf(",")+1);
            if(negat)
                return negative + finit.replace(',',' ');
            return finit.substring(finit.indexOf(",")+1);

        }
        String answerrr = ans.toString().replace(',',' ');
        if(negat)
            return negative + answerrr;
        return answerrr;
    }

    private String convertChunk(int num){
        StringBuilder local = new StringBuilder();
        if(num >= 100){
            local.append(" "+smalls[num/100] + " ");
            local.append("hundred ");
            num %= 100;
        }
        if(num >=10 && num <=19){
            local.append(smalls[num]+ " ");
        }else if(num >=20){
            local.append(tens[num/10]);
            num %= 10;
        }
        if(num >=1 && num <= 9){
            local.append(" "+ smalls[num]+",");
        }
        return local.substring(0);
    }

    public static void main(String[] args){
        EngInt test = new EngInt();
        System.out.println(test.convert(-123));
        System.out.println(test.convert(-1234));
        System.out.println(test.convert(1234));
        System.out.println(test.convert(12345));
    }
}
