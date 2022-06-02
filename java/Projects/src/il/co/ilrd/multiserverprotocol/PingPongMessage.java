package il.co.ilrd.multiserverprotocol;

import com.sun.xml.internal.ws.developer.Serialization;

import java.io.Serializable;

public class PingPongMessage implements Message<PingPongKeys, Void> {
    @Serialization
    private static final long serialVersionUID = 1L;
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
        //return key.equals(PingPongKeys.PING)?" "+ PingPongKeys.PONG:""+PingPongKeys.PING;
        return "PingPongMessage";
    }
}
