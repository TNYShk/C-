package il.co.ilrd.megaserver;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class Client3TCP {
    public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
        SocketChannel s = SocketChannel.open(new InetSocketAddress("localhost", 10523));
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
