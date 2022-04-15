package il.co.ilrd.quiz7;

import java.io.IOException;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Map;

public class Test {
    public static void main(String[] args) throws Exception {
       Map<String, String> premiumPhone = new Hashtable<>();
        premiumPhone.put("Apple", "iPhone");
        premiumPhone.put("samsung", "galaxy");
        premiumPhone.put("HTC", "one");


        Iterator<String> iter = premiumPhone.keySet().iterator();


            System.out.println(premiumPhone.values());

        while (iter.hasNext()){
                System.out.println(premiumPhone.get(iter.next()));
                premiumPhone.put("Sony", "Xperia");
        }

        try{
            Derived d = new Derived();
            throw new IOException();
        }

        catch(IOException e){
            e.printStackTrace();
            System.err.println("here");
            throw new RuntimeException();

            }

    }

}
