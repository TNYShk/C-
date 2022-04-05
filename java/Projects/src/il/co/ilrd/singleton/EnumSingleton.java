package il.co.ilrd.singleton;

public enum EnumSingleton {
    SINGLETON;

    EnumSingleton(){}

    public static EnumSingleton getInstance(){
       return SINGLETON;
    }
}
