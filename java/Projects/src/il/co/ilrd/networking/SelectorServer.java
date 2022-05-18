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
import java.util.Scanner;
import java.util.Set;

public class SelectorServer {
    //private final int TCPort;
   private final int UDPort;
    SocketAddress localport;

    ServerSocketChannel tcpserver;
    DatagramChannel udpserver;
    private SelectionKey sKey;
    DatagramChannel broadccast;

    private Selector selector;
    private volatile boolean isRun;
    private ByteBuffer byteBuf = ByteBuffer.allocate(1024);
    private final ByteBuffer welcomeBuf = ByteBuffer.wrap("Welcome to Chat!\n".getBytes());

    public SelectorServer(int port, int broadcast) {
        localport = new InetSocketAddress(port);
        UDPort = broadcast;
        isRun = true;
    }

    public void InitServer() throws IOException {
        tcpserver = ServerSocketChannel.open();
        udpserver = DatagramChannel.open();
        broadccast = DatagramChannel.open();

        tcpserver.socket().bind(localport);
        udpserver.socket().bind(localport);
        broadccast.socket().bind(new InetSocketAddress(UDPort));

        tcpserver.configureBlocking(false);
        udpserver.configureBlocking(false);
        broadccast.configureBlocking(false);
        int ops = tcpserver.validOps();

        selector = Selector.open();

        tcpserver.register(selector, SelectionKey.OP_ACCEPT);
        sKey = tcpserver.register(selector,ops,null);
        udpserver.register(selector, SelectionKey.OP_READ);
        broadccast.register(selector, SelectionKey.OP_READ);

        System.out.println("Server Started on port: " + localport + "!");

        listenServer();
    }

    public void listenServer() throws IOException {
        synchronized (this) {
            try {
            Iterator<SelectionKey> iter;
            SelectionKey key;

            while (isRun) {
                    selector.select();
                    iter = selector.selectedKeys().iterator();
                    // Iterate through the Set of keys.

                    while (iter.hasNext()) {
                        key = iter.next();
                        iter.remove();

                        Channel c = key.channel();

                        if (key.isAcceptable())
                            handleAccept(key);
                            // tcpserver.accept().socket();
                        else if (key.isReadable()) {
                            if ((c == udpserver) || (c == broadccast)) {
                                readableUDP(key);
                            } else {
                                handleRead(key); /* tcp read*/
                            }
                        }
                    }
            }
            } catch (IOException e) {
                    throw new RuntimeException(e);
            } finally {
                cancel();
            }
        }
    }


    public void cancel() throws IOException {
        isRun = false;
        broadccast.close();
        udpserver.close();
        tcpserver.close();
        selector.close();
    }

    private void readableUDP(SelectionKey key) throws IOException {
        DatagramChannel clientCh = (DatagramChannel)  key.channel();
        SocketAddress clientAdrs = clientCh.receive(byteBuf);
        System.out.println("write: ");
        Scanner sc = new Scanner(System.in);
        String response = sc.nextLine();

        System.out.println(new String(byteBuf.array()).trim());
        byteBuf.flip();
        clientCh.send(byteBuf,clientAdrs);
        byteBuf.clear();
        broadcast(response);

    }

    private void handleAccept(SelectionKey key) throws IOException {
        SocketChannel sc = ((ServerSocketChannel) key.channel()).accept();
        String address = sc.socket().getInetAddress().toString() + ":" + sc.socket().getPort();
        sc.configureBlocking(false);
        sc.register(selector, SelectionKey.OP_READ, address);
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
        SelectorServer server = new SelectorServer(10523,10521);
        server.InitServer();

    }
}