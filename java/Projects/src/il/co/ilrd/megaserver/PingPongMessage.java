package il.co.ilrd.megaserver;

import java.io.Serializable;

public class PingPongMessage implements Message<PingPongKeys, Void>, Serializable {
    private PingPongKeys key;
    public PingPongMessage(PingPongKeys key) {
        this.key = key;
    }
    @Override
    public PingPongKeys getKey() {
        return key;
    }

    @Override
    public Void getData() {
        return null;
    }
    @Override
    public String toString(){
        return key.equals(PingPongKeys.PING)?" "+ PingPongKeys.PONG:""+PingPongKeys.PING;
        //return ""+ this.key;
    }
}
