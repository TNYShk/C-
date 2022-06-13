package datastructures;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class StringRecursion {
    private void addParen(ArrayList<String> list, int leftRem, int rightRem, char[]str, int idx){
        if(leftRem< 0 || leftRem> rightRem) return; //invalid situation

        if(leftRem==0 && rightRem == 0){
            list.add(String.copyValueOf(str));
        }else{
            str[idx] = '(';
            addParen(list,leftRem-1, rightRem,str, idx+1);
            str[idx] = ')';
            addParen(list,leftRem, rightRem -1, str, idx+1);
        }
    }

    public ArrayList<String> generateParenthesis(int howMany){
        char[]str = new char[2 * howMany];
        ArrayList<String> ans = new ArrayList<>();
        addParen(ans,howMany,howMany,str,0);
        return ans;
    }

    public static void triminator(String path) throws FileNotFoundException {
        Scanner textFile = new Scanner(new File(path));
        ArrayList<String> file = new ArrayList<>();


        while(textFile.hasNext()){
            file.add(textFile.next().trim().toUpperCase());
        }

        System.out.println(file);
        Collections.sort(file);
        System.out.println(file);


        textFile.close();

    }

    public static void main(String[] args) throws FileNotFoundException {
        StringRecursion test = new StringRecursion();
        List<String> ans = test.generateParenthesis(3);
        System.out.print(ans);
        //triminator("/home/tanya/F1.txt");
        ArrayList<Integer> checkSome = new ArrayList<>(5);
        checkSome.add(11);
        checkSome.add(12);
        checkSome.add(13);
        checkSome.add(14);
        checkSome.add(15);
        System.out.println("\n"+ checkSome.size());
        checkSome.remove(0);
        System.out.println(checkSome.size());
    }
}
