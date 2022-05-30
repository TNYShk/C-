package il.co.ilrd.varonis;

import java.io.File;
import java.util.HashMap;

public class Factory {
    private HashMap<File,Component> factoryFun = new HashMap<>();



    interface Component{
        double operate(String a, String b);
    }
}
