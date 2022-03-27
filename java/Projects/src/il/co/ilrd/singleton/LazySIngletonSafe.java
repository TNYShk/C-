package il.co.ilrd.singleton;

public class LazySIngletonSafe {
    private static LazySIngletonSafe instance = null;

    private LazySIngletonSafe(){}

    public static synchronized LazySIngletonSafe getInstance(){
        if (null == instance){
            instance = new LazySIngletonSafe();
        }
        return instance;
    }
}
