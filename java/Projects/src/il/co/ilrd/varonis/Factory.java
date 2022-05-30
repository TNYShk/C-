package il.co.ilrd.varonis;


import jdk.nashorn.internal.codegen.CompilerConstants;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.function.Function;

public class Factory {

    //private HashMap<String, Function<String, Void>> operations = new HashMap<>();
    StringCounter test = new StringCounter("/Users/tanyashkolnik/Documents/F1.txt");
    public Factory() throws IOException {
     //operations.put("split",test.printSplit("-c"));
    }

    public static void main(String[] args) throws IOException {
        StringCounter test = new StringCounter("/Users/tanyashkolnik/Documents/F1.txt");
        test.work();
        test.produceOutput();
        test.printSplit("-c");
        test.printSplit("-n");
        test.printSplit("-s");
        test.maxWord();
        test.sortDesc();
        test.sortAsc();



    }

}


