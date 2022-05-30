package il.co.ilrd.varonis;


import jdk.nashorn.internal.codegen.CompilerConstants;


import java.io.IOException;
import java.util.HashMap;

import java.util.Scanner;


public class Factory {


    //StringCounter test = new StringCounter("/Users/tanyashkolnik/Documents/F1.txt");
    public Factory() throws IOException {

    }

    public static void main(String[] args) throws IOException {

        StringCounter test = new StringCounter("/Users/tanyashkolnik/Documents/F1.txt");
        System.out.println("enter desired command: ");
        test.counter();
        test.produceOutput();
        Scanner sc = new Scanner(System.in);
       String input =  sc.nextLine();
       boolean keepIt = true;
       while(keepIt){

        if(input.equals("split -c")){
            test.printSplit("-c");
         break;
        }
      if(input.equals("split -n")){
          test.printSplit("-n");
          break;
      }
       if( input.equals("split -s")){
           test.printSplit("-s");
           break;
       }
       if(input.equals("exit"))
           keepIt  = false;
        else{
           test.operate(input);
           input =  sc.nextLine();
        }

       }

       /*
        test.counter();
        test.produceOutput();
        //test.printSplit("-c");
        //test.printSplit("-n");
        //test.printSplit("-s");
        test.maxWord();
        test.sortDesc();
        test.sortAsc();
*/


    }

}


