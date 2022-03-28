package il.co.ilrd.singleton;

public enum EnumSingleton {
    SINGLETON;

    public static EnumSingleton getInstance(){
       return SINGLETON;
    }
}
