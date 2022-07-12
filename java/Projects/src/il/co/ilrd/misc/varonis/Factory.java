package il.co.ilrd.misc.varonis;

import java.io.IOException;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

public class Factory {
    //Varonis
    public static String setDefaultPathtoFile(String filename){
        Path currentRelativePath = Paths.get("");
        String path = currentRelativePath.toAbsolutePath().toString();
        path = path.concat("/"+filename);
        System.out.println(path);
        return path;
    }
    /**
     * load a text file into the factory
     * perform various operations on the files' content and output result as a new file
     * params:
     *      "split -c" = sorted words separated by a comma (,)
     *      "split -s" = sorted words separated by space
     *      "split -n" = sorted words separated by new line
     *      "count" = sorted list of words and their count
     *
     *      "by" = print on screen the most common word in file
     *
     */
    public static void main(String[] args) throws IOException {

        StringFactory test = new StringFactory("/Users/tanyashkolnik/IdeaProjects/textFactory/The Beatles - Help.txt");

        test.initDictionary();
        test.produceOutput();

        System.out.println("enter desired command: ");

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
            if(input.equals("split -s")){
                test.printSplit("-s");
                break;
            }
            else{
                if(input.equals("by") || input.equals("count"))
                    test.operate(input);
            }
            input = sc.nextLine();
        }


        System.out.println("GoodBye!");
        Path currentRelativePath = Paths.get("");
        String path = currentRelativePath.toAbsolutePath().toString();
        path = path.concat("/wordCounter.txt");
        Files.delete(Paths.get(path));

    }
}


