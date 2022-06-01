package il.co.ilrd.multiserverprotocol;

import java.io.Serializable;

public class ServerMessage implements Message<ServerProtocol, Message<?,?>>, Serializable {
    private static final long serialVersionUID = 1L;
    private ServerProtocol serverProtocol;
private Message<?,?> msg;


    public ServerMessage(ServerProtocol serverProtocol, Message<?, ?> msg) {
        this.serverProtocol = serverProtocol;
        this.msg = msg;
    }

    @Override
    public ServerProtocol getKey() {
        return serverProtocol;
    }

    @Override
    public Message<?, ?> getData() {
        return msg;
    }

    @Override
    public String toString(){return "ServerMessage";}
}
