package il.co.ilrd.networking;

import jdk.jfr.internal.Utils;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.Iterator;
import java.util.Set;

public class SelectorServer {
    //private final int TCPort;
   // private final int UDPort;
    SocketAddress localport;
    ServerSocketChannel tcpserver;
    DatagramChannel udpserver;
    private Selector selector;
    private volatile boolean isRun;
    private ByteBuffer byteBuf = ByteBuffer.allocate(512);
    private final ByteBuffer welcomeBuf = ByteBuffer.wrap("Welcome to Chat!\n".getBytes());

    public SelectorServer(int port) {
        localport = new InetSocketAddress(port);
        isRun = true;
    }

    public void InitServer() throws IOException {
        tcpserver = ServerSocketChannel.open();
        udpserver = DatagramChannel.open();

        tcpserver.socket().bind(localport);
        udpserver.socket().bind(localport);

        tcpserver.configureBlocking(false);
        udpserver.configureBlocking(false);

        selector = Selector.open();

        tcpserver.register(selector, SelectionKey.OP_ACCEPT);
        udpserver.register(selector, SelectionKey.OP_READ);

        System.out.println("Server Started on port: " + localport + "!");

        listenServer();
    }

    public void listenServer() {

        while (isRun) {
            try {
                selector.select();
                Set<SelectionKey> keys = selector.selectedKeys();

                // Iterate through the Set of keys.
                Iterator<SelectionKey> iter = keys.iterator();
                SelectionKey key;

                while (iter.hasNext() ) {
                    key = iter.next();
                    Channel c = key.channel();

                    if (key.isAcceptable() && c == tcpserver) {
                        this.handleAccept(key);
                       // tcpserver.accept().socket();

                    } else if (key.isReadable() && c == udpserver) {
                        //udpserver.socket();
                        this.readableUDP(key);

                    }else if(key.isReadable() ) {
                        this.handleRead(key); /* tcp read*/
                    }
                }
                iter.remove();

            } catch (IOException e) {
                throw new RuntimeException(e);
            }

        }

    }

    private void readableUDP(SelectionKey key) throws IOException {
        DatagramChannel clientCh = (DatagramChannel)  key.channel();
        SocketAddress clientAdrs = clientCh.receive(byteBuf);
        System.out.println("hi!");
        System.out.println(new String(byteBuf.array()).trim());
        byteBuf.flip();
        clientCh.send(byteBuf,clientAdrs);
        byteBuf.clear();

    }

    private void handleAccept(SelectionKey key) throws IOException {
        SocketChannel sc = ((ServerSocketChannel) key.channel()).accept();
        String address = sc.socket().getInetAddress().toString() + ":" + sc.socket().getPort();
        sc.configureBlocking(false);
        sc.register(selector, SelectionKey.OP_READ /*| SelectionKey.OP_ACCEPT*/);
        sc.write(welcomeBuf);
        welcomeBuf.rewind();
        System.out.println("accepted connection from: "+ address);
    }

    private void handleRead(SelectionKey key) throws IOException {
        SocketChannel ch = (SocketChannel) key.channel();
        StringBuilder sb = new StringBuilder();
        byteBuf.clear();
        int read = 0;
        while( (read = ch.read(byteBuf)) > 0 ) {
            byteBuf.flip();
            byte[] bytes = new byte[byteBuf.limit()];
            byteBuf.get(bytes);
            sb.append(new String(bytes));
            byteBuf.clear();
        }
        String msg;
        if(read < 0) {
            msg = key.attachment() + " has left the building\n";
            ch.close();
        }
        else {
            msg = key.attachment()+" : "+ sb;
        }
        //System.out.println(msg);
        broadcast(msg);
    }

    private void broadcast(String msg) throws IOException {
        ByteBuffer msgBuf = ByteBuffer.wrap(msg.getBytes());
        for(SelectionKey key : selector.keys()) {
            if(key.isValid() && key.channel() instanceof SocketChannel) {
                SocketChannel sch = (SocketChannel) key.channel();
                sch.write(msgBuf);
                msgBuf.rewind();
            }
        }
    }

    public static void main(String[] args) throws IOException {
        SelectorServer server = new SelectorServer(10523);
        server.InitServer();

    }
}
