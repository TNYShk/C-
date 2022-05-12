package il.co.ilrd.dsexam;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class HttpUtilityTester {

    public static void main(String[] args) {
        // test sending GET request
        System.out.println("enter word: ");
        Scanner input = new Scanner(System.in);
        String word = input.nextLine();
        System.out.println(word);
        String requestURL = "https://api.dictionaryapi.dev/api/v2/entries/en/";
        requestURL = requestURL.concat(word);
        System.out.println(requestURL);
        try {
            Dictionary.sendGetRequest(requestURL);
            String result = Dictionary.readSingleLineRespone();
           /* String[] response = Dictionary.readMultipleLinesRespone();
            for (String line : response) {
                System.out.println(line);
            }*/
            System.out.println(result);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        Dictionary.disconnect();


        System.out.println("=====================================");

      /*  // test sending POST request
        Map<String, String> params = new HashMap<String, String>();
        requestURL = "https://api.dictionaryapi.dev/api/v2/entries/en/";
        params.put("word", "estate");
        params.put("origin", "meaning");

        try {
            //Dictionary.sendGetRequest(requestURL);
            Dictionary.sendPostRequest(requestURL, params);
            String[] response = Dictionary.readMultipleLinesRespone();
            for (String line : response) {
                System.out.println(line);
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        Dictionary.disconnect();*/
    }
}
