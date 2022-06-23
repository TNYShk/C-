package tcode.wordle;

import java.io.IOException;
import java.util.Scanner;

public class HttpUtilityTester {

    public static void main(String[] args) {
        // test sending GET request
        System.out.println("enter word: ");
        Scanner input = new Scanner(System.in);
        String word = input.nextLine();
        System.out.println(word);
        //String requestURL = "https://api.dictionaryapi.dev/api/v2/entries/en/";  /* free Dictionary, no key required*/
        String requestURL = "https://dictionaryapi.com/api/v3/references/ithesaurus/json/";
        //String requestURL = "https://dictionaryapi.com/api/v3/references/thesaurus/json/";
        String myAPI = "?key=b7f20b3e-7111-404c-a30b-28751d6a027b"; /* thesaurus MW*/
        String anotherAPI = "?key=e3b0322b-c7f8-401c-ac77-ca4c84aa62a5";  /* intermediate thesaurus MW*/
        requestURL = requestURL.concat(word);
        requestURL = requestURL.concat(anotherAPI); /* MW required API key*/
        System.out.println(requestURL);
        try {
            HttpUtility.sendGetRequest(requestURL);
            //String result = Dictionary.readSingleLineRespone();
          String[] response = HttpUtility.readMultipleLinesRespone();
            for (String line : response) {
                System.out.println(line);
            }
            //System.out.println(result);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        HttpUtility.disconnect();


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
