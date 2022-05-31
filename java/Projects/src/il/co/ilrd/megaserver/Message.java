package il.co.ilrd.megaserver;

import java.io.Serializable;

public interface Message<K,D> extends Serializable {
    public K getKey();
    public D getData();
}
