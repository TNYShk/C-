package il.co.ilrd.megaserver;

import java.io.Serializable;

public class ServerMessage implements Message<ServerProtocol, Message<?,?>>, Serializable {
private Message<?,?> msg;
private ServerProtocol serverProtocol;

    public ServerMessage(ServerProtocol serverProtocol, Message<?, ?> msg) {
        this.msg = msg;
        this.serverProtocol = serverProtocol;
    }

    @Override
    public ServerProtocol getKey() {
        return serverProtocol;
    }

    @Override
    public Message<?, ?> getData() {
        return msg;
    }
}
