package il.co.ilrd.singleton;

public class LazySIngleton {
    private static LazySIngleton instance = null;

    private LazySIngleton(){}

    public static synchronized LazySIngleton getInstance(){
        if (null == instance){
            instance = new LazySIngleton();
        }
        return instance;
    }
}
