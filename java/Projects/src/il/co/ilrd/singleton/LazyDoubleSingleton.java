package il.co.ilrd.singleton;

import java.util.concurrent.locks.ReentrantLock;

public class LazyDoubleSingleton {
    private static volatile LazyDoubleSingleton instance;
    private static volatile ReentrantLock lock = new ReentrantLock();

    private LazyDoubleSingleton(){}

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
public void run(){
        System.out.println("thread running!");
}
    /* synchronized  version//

        public static LazyDoubleSingleton getInstance(){
            if (null == instance) {
                synchronized (LazyDoubleSingleton.class){
                    if (null == instance) {
                        instance = new LazyDoubleSingleton();
                    }
                }
            }
            return instance;
        }
     */
}
