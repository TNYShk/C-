package il.co.ilrd.megaserver;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;


public class Client1TCP implements SerializeIt{
    private SocketChannel client;
    private ByteBuffer buffer;

    public static void main(String args[]) throws IOException, ClassNotFoundException, InterruptedException {
        PingPongMessage messagePing1 = new PingPongMessage(PingPongKeys.PING);
        ServerMessage message1 = new ServerMessage(ServerProtocol.PINGPONG, messagePing1);
        PingPongMessage messagePing2 = new PingPongMessage(PingPongKeys.PONG);
        ServerMessage message2 = new ServerMessage(ServerProtocol.PINGPONG, messagePing2);
        Client1TCP client = new Client1TCP("192.168.68.101", 10523);


        for (int i = 0; i < 6; ++i) {
            client.sendMessage(message1);
            client.sendMessage(message2);
        }
        //TimeUnit.SECONDS.sleep(5);
        client.closeClient();

    }



    public Client1TCP(String address, int port) {
        try {
            client = SocketChannel.open(new InetSocketAddress(address, port));
            buffer = ByteBuffer.allocate(8192);
            System.out.println("Connected");
        } catch(IOException e) {
            System.out.println(e);
        }
    }

    public void closeClient() throws IOException {
        client.close();
    }

    public void sendMessage(Message<?, ?> msg) throws IOException, ClassNotFoundException {

        buffer = buffer.put(serializeB(msg));
        try {
            buffer.flip();
            client.write(buffer);
            buffer.clear();
            client.read(buffer);
            buffer.clear();

            Object object = deserialize(buffer);
            if (!(object instanceof ServerMessage)) {
                throw new ClassCastException();
            }
            ServerMessage serverMessage = (ServerMessage)object;
            System.out.println(serverMessage.getData().getKey());

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    @Override
    public Object deserialize(ByteBuffer buffer) throws IOException, ClassNotFoundException {
        if (buffer == null) {
            return null;
        }

        try (ByteArrayInputStream b = new ByteArrayInputStream(buffer.array());
             ObjectInputStream o = new ObjectInputStream(b)) {
                return o.readObject();
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
