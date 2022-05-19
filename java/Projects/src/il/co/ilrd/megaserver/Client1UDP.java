package il.co.ilrd.megaserver;

import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;

public class Client1UDP {
    private DatagramSocket socket;
    private InetAddress address;
    private ByteBuffer buffer;



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
        address = InetAddress.getByName("192.168.68.101");
        buffer = ByteBuffer.allocate(8192);
    }

    public void sendEcho(ServerMessage msg) throws IOException, ClassNotFoundException {
        buffer = buffer.put(serialize(msg));
        DatagramPacket packet = new DatagramPacket(buffer.array(), buffer.array().length, address, 10521);
        socket.send(packet);
        packet = new DatagramPacket(buffer.array(), buffer.array().length);
        socket.receive(packet);
        ServerMessage serverMessage = (ServerMessage)deserialize(packet.getData());
        System.out.println("udp client got: " + serverMessage.getData().getKey());

    }

    public void close() {
        socket.close();
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
