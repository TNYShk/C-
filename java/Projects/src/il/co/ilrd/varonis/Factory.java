package il.co.ilrd.varonis;

import java.io.IOException;

import java.util.Scanner;

public class Factory {

    public static void main(String[] args) throws IOException {

        StringCounter test = new StringCounter("/Users/tanyashkolnik/Documents/F1.txt");
        System.out.println("enter desired command, (assuming your'e a good user) : ");
        test.counter();
        //test.produceOutput();
        Scanner sc = new Scanner(System.in);
        String input = sc.nextLine();
        while(!input.equals("exit")){

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
           else{
               test.operate(input);
               break;
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
        System.out.println("GoodBye!");

    }

}


