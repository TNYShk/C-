package il.co.ilrd.multiserverprotocol;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class ClientTCPTest {
    private ByteBuffer buffer;

    private SocketChannel socketChannel;

    public ClientTCPTest() throws IOException {
        buffer = ByteBuffer.allocate(1024);
        socketChannel = SocketChannel.open(new InetSocketAddress("10.1.0.77", 10523));
        socketChannel.configureBlocking(false);
    }

    public void communicate() throws IOException, InterruptedException, ClassNotFoundException {
        PingPongMessage msgping = new PingPongMessage(PingPongKeys.PING);
        ServerMessage smsg = new ServerMessage(ServerProtocol.PINGPONG, msgping);
        buffer = buffer.put(serialize(smsg));
        buffer.flip();
       // buffer.clear();
        socketChannel.write(buffer);
        Thread.sleep(1000);
        //buffer.rewind();
        buffer.clear();

        socketChannel.read(buffer);

        ServerMessage serverMessage = (ServerMessage)deserialize(buffer.array());

        System.out.println("message form server: " + serverMessage.getData().toString());

        socketChannel.close();

    }


    public byte[] serialize(Object object) throws IOException {
        try (ByteArrayOutputStream bos = new ByteArrayOutputStream();
             ObjectOutputStream oos = new ObjectOutputStream(bos)) {
                oos.writeObject(object);
                oos.flush();
                return bos.toByteArray();

        }
    }

    private static Object deserialize(byte[] bytes) throws IOException, ClassNotFoundException {
        if (bytes == null) {
            return null;
        }

        try (ByteArrayInputStream b = new ByteArrayInputStream(bytes);
             ObjectInputStream o = new ObjectInputStream(b)) {
                return o.readObject();
            }
        }

}
