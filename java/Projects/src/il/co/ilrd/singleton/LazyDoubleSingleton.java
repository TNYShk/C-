package il.co.ilrd.singleton;

import java.util.concurrent.locks.ReentrantLock;

public class LazyDoubleSingleton {
    private static LazyDoubleSingleton instance;
    static ReentrantLock lock = new ReentrantLock();

    private LazyDoubleSingleton(){
    }
    public static LazyDoubleSingleton getInstance(){
        if (instance == null) {
            lock.lock();
            if (instance == null) {
                instance = new LazyDoubleSingleton();
            }
        }
        lock.unlock();
        return instance;

    }
}
