package il.co.ilrd.multiserverprotocol;

import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;

public class Client1UDP {

    private DatagramSocket socket;
    private InetAddress address;


    private ByteBuffer buf;

    public static void main(String args[]) throws IOException, ClassNotFoundException {
        Client1UDP client = new Client1UDP();
        PingPongMessage messagePing1 = new PingPongMessage(PingPongKeys.PONG);
        ServerMessage message1 = new ServerMessage(ServerProtocol.PINGPONG, messagePing1);

        for (int i = 0; i < 4; ++i) {
            client.sendEcho(message1);
        }
        client.close();
    }


    public Client1UDP() throws SocketException, UnknownHostException {
        socket = new DatagramSocket();
        address = InetAddress.getByName("192.168.68.107");
       // address = InetAddress.getByName("localhost");
        buf = ByteBuffer.allocate(8192);

    }

    public void sendEcho(Message<?, ?> msg) throws IOException, ClassNotFoundException {

        buf = buf.put(serialize(msg));
//		buffer.clear();
        DatagramPacket packet = new DatagramPacket(buf.array(), buf.array().length, address, 11111);
        socket.send(packet);
//		buffer.clear();
        packet = new DatagramPacket(buf.array(), buf.array().length);
//		buffer.clear();
        socket.receive(packet);
//		received = new String(packet.getData(), 0, packet.getLength());
        ServerMessage serverMessage = (ServerMessage)deserialize(packet.getData());
        System.out.println("udp got?: " + serverMessage.getData().getKey());

    }

    public void close() {
        socket.close();
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
