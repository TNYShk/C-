package il.co.ilrd.factory;
/*
    Factory Design Pattern WS
    by Tanya Shk
    April 17, 2022
    reviewed by Yehuda

 */
import java.util.HashMap;

import java.util.function.Function;
public class Factory<K, T, D> {
    private HashMap<K, Function<D,? extends T>> factoryFun = new HashMap<>();

    public void add(Function<D,? extends T> funObject, K key){
        factoryFun.put(key,funObject);
    }

    public T create(K key){
        return this.create(key, null);
    }

    public T create (K key, D data){
        return factoryFun.get(key).apply(data);
    }

    public int mapSize(){
        return this.factoryFun.size();
    }
}
