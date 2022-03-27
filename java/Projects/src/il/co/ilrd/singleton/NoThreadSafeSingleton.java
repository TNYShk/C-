package il.co.ilrd.singleton;

//not thread safe
public class NoThreadSafeSingleton {
    private static NoThreadSafeSingleton instance;

    private NoThreadSafeSingleton(){}

    public static NoThreadSafeSingleton getInstance(){
        if(null == instance){
            instance = new NoThreadSafeSingleton();
        }

        return instance;
    }
}
