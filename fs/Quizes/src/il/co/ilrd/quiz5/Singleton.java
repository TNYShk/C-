package il.co.ilrd.quiz5;

import com.sun.xml.internal.bind.v2.runtime.unmarshaller.XsiNilLoader;

public class Singleton {
    private static Singleton instance;
    private static String name;
    private int counter = 0;
    private Singleton(){
        this.name = "tanya";
       ++counter;
    }

    public static Singleton getInstance(){
        if(instance == null){
          synchronized (Singleton.class){
                if (null == instance) {
                    instance = new Singleton();
                }
            }
        }
        return instance;
    }
    public static void main(String[] args){
        Singleton t = Singleton.getInstance();
        System.out.println(t.name + t.counter);
        Singleton b = Singleton.getInstance();
        System.out.println(b.name + b.counter);
        Singleton tt = new Singleton();
        System.out.println(tt.name + tt.counter);


    }
}


