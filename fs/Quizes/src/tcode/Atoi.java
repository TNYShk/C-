package tcode;

public class Atoi {

    public int myAtoi(String s){
        StringBuilder str = new StringBuilder(s.trim());
        int sign = 1;
        int i = 0;
        int num = 0;
        if(str.charAt(i) == '-') {
            sign = -1;
            ++i;
        }
        else if(str.charAt(i) == '+'){
            sign = 1;
            ++i;
        }
        while(i<str.length() && (Character.isDigit(str.charAt(i)))){
            if(( num> Integer.MAX_VALUE/10) || (num == Integer.MAX_VALUE / 10 && str.charAt(i) - '0' > 7) ){
                return sign ==1 ? Integer.MAX_VALUE: Integer.MIN_VALUE ;
            }
                num *= 10;
                num +=(str.charAt(i++) - '0');

            }
           return  (sign * num);
        }

private enum State { Q0, Q1, Q2, QZ}
    static class  StateMachine{
        private State currentState;
        private int result, sign;

        public StateMachine(){
            currentState = State.Q0;
            result = 0;
            sign = 1;
        }

        private void transitionQ1(char cc){
            sign = (cc == '-')? -1: 1;
            currentState = State.Q1;
        }

        private void transitionQ2(int digit){
            currentState = State.Q2;
            appendDigit(digit);
            /*
            char cc
            if(Character.isDigit(cc))
             */
        }
        private void transitionDeath(){
            sign = 1;
            currentState = State.QZ;
        }

        private void appendDigit(int digit){
            if ((result > Integer.MAX_VALUE / 10) ||
                    (result == Integer.MAX_VALUE / 10 && digit > Integer.MAX_VALUE % 10)) {
                result = (sign ==1)? Integer.MAX_VALUE: Integer.MIN_VALUE;
                transitionDeath();
            }else{
                result = result * 10 + digit;
            }
        }

        public void transition(char cc){
            if(currentState ==  State.Q0){
                if(cc == '-' || cc == '+')
                    transitionQ1(cc);
                else if(Character.isDigit(cc))
                    transitionQ2(cc- '0');
                else
                    transitionDeath();
            }else if(currentState ==State.Q1 || currentState == State.Q2){
                if(Character.isDigit(cc))
                    transitionQ2(cc - '0');
                else
                    transitionDeath();
            }
        }

        public int getResult(){
            return sign * result;
        }

        public State getState(){
            return currentState;
        }
    }

    public static void main(String[] args){
        Atoi test = new Atoi();

        String s1 = " 2147483648";
        String s2 = " 2147483646";
        String s3 = " -2147483647";
        String s4 = "-91283472332";
        System.out.println(test.myAtoi(s1));
        System.out.println(test.myAtoi(s2));
        System.out.println(test.myAtoi(s3));
        System.out.println(test.myAtoi(s4));
        s1 = s1.trim();
        s2 = s2.trim();
        s3 = s3.trim();
        s4 = s4.trim();
        System.out.println("State Machine:");
        StateMachine Q = new StateMachine();
        for(int i = 0; i<s4.length() && Q.getState() !=State.QZ; ++i)
            Q.transition(s4.charAt(i));
        System.out.println(Q.getResult());
    }
}
