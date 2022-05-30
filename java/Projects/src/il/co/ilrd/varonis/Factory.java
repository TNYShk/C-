package il.co.ilrd.varonis;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;

public class Factory<K,V> {
    private HashMap<K,V> funcMap = new HashMap<>();
    StringCounter test = new StringCounter("/Users/tanyashkolnik/Documents/F1.txt");
    public Factory() throws IOException {

    }

    public static void main(String[] args) throws IOException {
        StringCounter test = new StringCounter("/Users/tanyashkolnik/Documents/F1.txt");
        StringCounter.work();
        StringCounter.produceOutput();
        StringCounter.printComma();
        StringCounter.maxWord();


    }

}


