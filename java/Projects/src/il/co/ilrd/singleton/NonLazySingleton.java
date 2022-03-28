package il.co.ilrd.singleton;

public class NonLazySingleton {
    private static final NonLazySingleton instance = new NonLazySingleton();

    private NonLazySingleton(){}

    public static NonLazySingleton getInstance(){
        return instance;
    }
}
