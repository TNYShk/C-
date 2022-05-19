package il.co.ilrd.megaserver;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class Client1TCP {
    public static void main(String args[]) throws IOException, ClassNotFoundException {
        PingPongMessage messagePing1 = new PingPongMessage(PingPongKeys.PONG);
        ServerMessage message1 = new ServerMessage(ServerProtocol.PINGPONG, messagePing1);

        Client1TCP client = new Client1TCP("192.168.68.101", 10523);

        client.sendMessage(message1);
    }

    private SocketChannel client;
    private ByteBuffer buffer;

    public Client1TCP(String address, int port) {
        try {
            client = SocketChannel.open(new InetSocketAddress(address, port));
            buffer = ByteBuffer.allocate(8192);
            System.out.println("Connected");
        } catch(IOException e) {
            System.out.println(e);
        }
    }

    public void sendMessage(Message<?, ?> msg) throws IOException, ClassNotFoundException {

        buffer = buffer.put(serialize(msg));


        try {
            buffer.rewind();
            client.write(buffer);
            buffer.clear();
            client.read(buffer);

            Object object = deserialize(buffer.array());
            buffer.flip();
            if (!(object instanceof ServerMessage)) {
                throw new ClassCastException();
            }
            ServerMessage serverMessage = (ServerMessage)object;
//			ServerProtocol protocol = serverMessage.getKey();
//			if (!(protocol instanceof PingPongMessage)) {
//				throw new ClassCastException();
//			}
            System.out.println("message data " + serverMessage.getData());
            System.out.println("message key" + serverMessage.getKey());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public byte[] serialize(Object object) throws IOException {
        try (ByteArrayOutputStream bos = new ByteArrayOutputStream()) {
            try (ObjectOutputStream oos = new ObjectOutputStream(bos)){
                oos.writeObject(object);
                oos.flush();
                return bos.toByteArray();
            }
        }
    }

    private static Object deserialize(byte[] bytes) throws IOException, ClassNotFoundException {
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
