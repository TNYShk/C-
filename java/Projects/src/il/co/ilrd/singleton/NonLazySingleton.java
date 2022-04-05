package il.co.ilrd.singleton;

/* eager initialization, no if null. static instance of Singleton
* its private static final. can't be created using constructor
* static variables are thread safe, thus this is thread safe.
* java promises static variables are thread safe
* final because this reference is not going to change, always reference this specific object INSTANCE. not related to thread safe. will also work without final
* */
public class NonLazySingleton {
    private static final NonLazySingleton INSTANCE = new NonLazySingleton();

    private NonLazySingleton(){}

    public static NonLazySingleton getInstance(){
        return INSTANCE;
    }
}
