package il.co.ilrd.singleton;

public class LazySIngleton {

    private LazySIngleton(){}

    static class LazySIngletonHolder {
        private static LazySIngleton instance = new LazySIngleton();
    }

    public static synchronized LazySIngleton getInstance(){
        return LazySIngletonHolder.instance;
    }
}
