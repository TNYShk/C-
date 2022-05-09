package il.co.ilrd.dsexam;
//is parentheses string valid

import java.util.Stack;

public class Question7 {
    Stack<String> verify = new Stack<>();

    public boolean checkParentheses(String str){
        verify.clear();

        for(int i=0;i<str.length();++i){
            char t = str.charAt(i);

            if(t == '{' || t== '(' || t == '<' || t =='['){
                String temp = "" + str.charAt(i);
                verify.push(temp);
            }
            if(t == '}' || t== ')' || t == '>' || t ==']'){
                char peek = verify.peek().charAt(0);
                if(t- peek == 2 || t - peek ==1) {

                    verify.pop();
                }
                else{
                    break;
                }
            }
        }
        return (verify.isEmpty());
    }

    public static void main(String[] args){
        String str = "(x+3*[4+6])<>";
        String str1 = "(8]*(6+2)+2)";

        Question7 test = new Question7();
        System.out.println(test.checkParentheses(str));
        System.out.println(test.checkParentheses(str1));
    }

}
