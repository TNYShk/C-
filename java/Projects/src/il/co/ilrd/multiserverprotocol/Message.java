package il.co.ilrd.multiserverprotocol;

import java.io.Serializable;

public interface Message<K,D> extends Serializable {
    public K getKey();
    public D getData();
}
