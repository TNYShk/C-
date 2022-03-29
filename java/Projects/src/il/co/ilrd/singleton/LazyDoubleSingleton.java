package il.co.ilrd.singleton;

import java.util.concurrent.locks.ReentrantLock;

public class LazyDoubleSingleton {
    private static LazyDoubleSingleton instance;
    static ReentrantLock lock = new ReentrantLock();

    private LazyDoubleSingleton(){
    }
    public static LazyDoubleSingleton getInstance(){

        if (null == instance) {
            lock.lock();
            if (null == instance) {
                instance = new LazyDoubleSingleton();
            }
            lock.unlock();
        }

        return instance;

    }

    /* without lock version//

        public static LazyDoubleSingleton getInstance(){
             if (instance == null) {
                synchronized (LazyDoubleSingleton.class){
                    if (instance == null) {
                        instance = new LazyDoubleSingleton();
              }
            }
        }
        return instance;
    }
     */
}
