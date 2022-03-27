package il.co.ilrd.singleton;

public class singletonNotLazyThreadSafe {
    private static final singletonNotLazyThreadSafe instance = new singletonNotLazyThreadSafe();

    private singletonNotLazyThreadSafe(){}

    public static singletonNotLazyThreadSafe getInstance(){
        return instance;
    }
}
