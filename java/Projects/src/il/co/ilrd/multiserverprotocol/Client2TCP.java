package il.co.ilrd.multiserverprotocol;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class Client2TCP {
    public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
        SocketChannel s = SocketChannel.open(new InetSocketAddress("192.168.68.107", 55555));
        ByteBuffer buffer;

        // s.configureBlocking(true);
        PingPongMessage msg = new PingPongMessage(PingPongKeys.PONG);
        ServerMessage smsg = new ServerMessage(ServerProtocol.PINGPONG, msg);


        buffer = ByteBuffer.wrap(SerializeIt.serializeB(smsg));

        //buffer.clear();
        s.write(buffer);
        buffer.clear();
        System.out.println("before read");
        s.read(buffer);
        buffer.clear();

        Object obj = deserialize(buffer.array());
        ServerMessage respond = (ServerMessage) obj;
        PingPongMessage ppmsg = (PingPongMessage) respond.getData();
        System.out.println("message from server: " + ppmsg.getKey());




        //s.close();

    }
    public static Object deserialize(byte[] bytes) throws IOException, ClassNotFoundException {
        if (bytes == null) {
            return null;
        }

        try (ByteArrayInputStream b = new ByteArrayInputStream(bytes)) {
            try (ObjectInputStream o = new ObjectInputStream(b)) {
                return o.readObject();
            }
        }
    }

}
