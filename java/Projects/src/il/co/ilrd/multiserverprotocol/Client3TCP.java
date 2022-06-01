package il.co.ilrd.multiserverprotocol;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class Client3TCP {
    public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
        SocketChannel s = SocketChannel.open(new InetSocketAddress("192.168.68.103", 10523));
        ByteBuffer buffer;

        // s.configureBlocking(true);

        ChatMessage msgC = new ChatMessage(ChatKeys.REGISTER, "tanya");
        ServerMessage smsg = new ServerMessage(ServerProtocol.CHAT, msgC);

        buffer = ByteBuffer.wrap(SerializeIt.serializeB(smsg));

        //buffer.clear();
        s.write(buffer);
        buffer.clear();
        System.out.println("before read");
        s.read(buffer);
        buffer.clear();

        Object obj = deserialize(buffer.array());
        ChatMessage chat = ((ChatMessage) obj);
        System.out.println("message from server: " + chat.getData());

        ChatMessage msgB = new ChatMessage(ChatKeys.BROADCAST, "positive for COVID");
        ServerMessage smsB = new ServerMessage(ServerProtocol.CHAT, msgB);

        buffer.clear();
        buffer = ByteBuffer.wrap(SerializeIt.serializeB(smsB));
        //System.out.println("message from server: " + chat.getData());
        s.write(buffer);
        buffer.clear();
       // System.out.println("before read");
        s.read(buffer);
        buffer.clear();

        Object objd = deserialize(buffer.array());
        ChatMessage chatd = ((ChatMessage) objd);
        System.out.println("message from server: " + chatd.getData());

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
