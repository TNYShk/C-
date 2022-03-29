package il.co.ilrd.singleton;

public class LazySIngleton {

    private LazySIngleton(){}

    static class LazySIngletonHelper {
        private static LazySIngleton instance = new LazySIngleton();
    }

    public static synchronized LazySIngleton getInstance(){
        return LazySIngletonHelper.instance;
    }
}
