package il.co.ilrd.megaserver;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class ClientTCPTest implements SerializeIt{
    private ByteBuffer buffer;
    private ServerMessage smsg;
    private SocketChannel socketChannel;

    public ClientTCPTest() throws IOException {
        buffer = ByteBuffer.allocate(1024);
        socketChannel = SocketChannel.open(new InetSocketAddress("192.168.68.101", 10523));
        socketChannel.configureBlocking(false);
    }

    public void communicate() throws IOException, InterruptedException, ClassNotFoundException {
        PingPongMessage msg = new PingPongMessage(PingPongKeys.PING);
        smsg = new ServerMessage(ServerProtocol.PINGPONG, msg);
        buffer.put(serialize(smsg));
        //buffer.rewind();
        buffer.clear();
        socketChannel.write(buffer);
        Thread.sleep(1000);
        buffer.rewind();

        socketChannel.read(buffer);


        Object obj = deserialize(buffer);
        ServerMessage respond = (ServerMessage) obj;
        System.out.println("message form server: " + respond.getData().toString());

        socketChannel.close();

    }


    @Override
    public Object deserialize(ByteBuffer buffer) throws IOException, ClassNotFoundException {
        if (buffer == null) {
            return null;
        }
        try (ByteArrayInputStream bAis = new ByteArrayInputStream(buffer.array())) {
            try (ObjectInputStream obj = new ObjectInputStream(bAis)) {
                return obj.readObject();
            }
        }

    }

    @Override
    public ByteBuffer serialize(Object serverMsg) throws IOException {
        try(ByteArrayOutputStream bos = new ByteArrayOutputStream()) {
            try (ObjectOutputStream oos = new ObjectOutputStream(bos)){
                oos.writeObject(serverMsg);
                oos.flush();
                return ByteBuffer.wrap(bos.toByteArray());
            }
        }

    }
}
