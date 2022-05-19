package il.co.ilrd.megaserver;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class ClientTCPTest implements SerializeIt{
    private ByteBuffer buffer;

    private SocketChannel socketChannel;

    public ClientTCPTest() throws IOException {
        buffer = ByteBuffer.allocate(1024);
        socketChannel = SocketChannel.open(new InetSocketAddress("192.168.68.101", 10523));
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


        Object obj = deserialize(buffer);
        buffer.flip();
        ServerMessage respond = (ServerMessage) obj;
        System.out.println("message form server: " + respond.getKey().toString());

        //socketChannel.close();

    }


    @Override
    public Object deserialize(ByteBuffer buffer) throws IOException, ClassNotFoundException {
        if (buffer == null) {
            return null;
        }
        //buffer.rewind();
        byte[] tempBuf = buffer.array();
        //buffer.rewind();
        try (ByteArrayInputStream bAis = new ByteArrayInputStream(tempBuf);
             ObjectInputStream obj = new ObjectInputStream(bAis)) {
                return obj.readObject();
            }
        }



    @Override
    public ByteBuffer serialize(Object serverMsg) throws IOException {
        try(ByteArrayOutputStream bos = new ByteArrayOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(bos)) {
                oos.writeObject(serverMsg);
                oos.flush();
                return ByteBuffer.wrap(bos.toByteArray());

        }

    }


}
