package il.co.ilrd.singleton;

public class NoThreadSafeSingleton {
    private static NoThreadSafeSingleton instance = null;

    private NoThreadSafeSingleton(){}

    public static NoThreadSafeSingleton getInstance(){
        if(null == instance){
            instance = new NoThreadSafeSingleton();
        }
        return instance;
    }
}
