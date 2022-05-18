package il.co.ilrd.megaserver;

public interface Message<K,D> {
    public K getKey();
    public D getData();
}
