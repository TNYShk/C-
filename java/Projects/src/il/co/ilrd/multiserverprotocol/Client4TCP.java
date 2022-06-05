package il.co.ilrd.multiserverprotocol;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

public class Client4TCP {
    private static Scanner scaner;
    private static ByteBuffer buffer;
    private static SocketChannel s;

    public Client4TCP() throws IOException {
        scaner = new Scanner(System.in);
        s = SocketChannel.open(new InetSocketAddress("192.168.1.198", 10523));
        buffer = ByteBuffer.allocate(8192);
    }

    public void produceRegisterMsg() throws IOException, ClassNotFoundException, InterruptedException {

        System.out.println("enter the name:");
        String data = scaner.nextLine();

        ChatMessage chatMsg = new ChatMessage(ChatKeys.REGISTER, data);
        ServerMessage sm = new ServerMessage(ServerProtocol.CHAT, chatMsg);

        buffer = ByteBuffer.wrap(SerializeIt.serializeB(sm));
        System.out.println(buffer.position());

        s.write(buffer);
        System.out.println(buffer.position());
        buffer.clear();
        System.out.println("wait for ans");
        s.read(buffer);

        Object obj = deserialize(buffer.array());
        ChatMessage chat = ((ChatMessage)obj);
        System.out.println("message from server: " + chat.getData());
    }

    public void send(String str) throws IOException, ClassNotFoundException {
        ChatMessage chatMsg = new ChatMessage(ChatKeys.BROADCAST, str);
        ServerMessage sm = new ServerMessage(ServerProtocol.CHAT, chatMsg);

        buffer = ByteBuffer.wrap(SerializeIt.serializeB(sm));

        s.write(buffer);
        buffer.clear();
        s.read(buffer);

        Object obj = deserialize(buffer.array());
        ChatMessage chat = ((ChatMessage)obj);
        System.out.println(chat.getData());
    }

    public void remove() throws IOException, ClassNotFoundException {

        System.out.println("enter the name:");
        String name = scaner.nextLine();

        ChatMessage chatMsg = new ChatMessage(ChatKeys.UNREGISTER, name);
        ServerMessage sm = new ServerMessage(ServerProtocol.CHAT, chatMsg);

        buffer = ByteBuffer.wrap(SerializeIt.serializeB(sm));

        s.write(buffer);
        buffer.clear();
        System.out.println("wait for ans");
        s.read(buffer);

        Object obj = deserialize(buffer.array());
        ChatMessage chat = ((ChatMessage)obj);
        System.out.println("message from server: " + chat.getData());
    }

    public void close() throws IOException {
        buffer.clear();
        s.close();
        scaner.close();
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

    public static void main(String [] argv) throws IOException, ClassNotFoundException, InterruptedException {
        Client4TCP sho = new Client4TCP();
        sho.produceRegisterMsg();

        String input = null;

        while (!(input = scaner.nextLine()).equals("bye")) {
            sho.send(input);

            buffer.clear();
            s.read(buffer);

            Object obj = deserialize(buffer.array());
            ChatMessage chat = ((ChatMessage)obj);
            System.out.println(chat.getData());
        }

        sho.remove();
        sho.close();
    }
}
