package il.co.ilrd.singleton;

public class LazySIngleton {

    private LazySIngleton(){}

    private static class LazySIngletonHolder {
         private static final LazySIngleton INSTANCE = new LazySIngleton();
    }

    public static LazySIngleton getInstance(){
        return LazySIngletonHolder.INSTANCE;
    }
}
