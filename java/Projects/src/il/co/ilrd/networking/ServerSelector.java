package il.co.ilrd.networking;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.Iterator;

public class ServerSelector {
    private final int port;
    private ServerSocketChannel ssc;
    private Selector selector;
    private ByteBuffer byteBuf = ByteBuffer.allocate(512);
    private SelectionKey selectionKey;
    private final ByteBuffer welcomeBuf = ByteBuffer.wrap("Welcome to Chat!\n".getBytes());

    public ServerSelector(int port) throws IOException {
        this.port = port;
        ssc = ServerSocketChannel.open();
        ssc.socket().bind(new InetSocketAddress(port));
        ssc.configureBlocking(false);
        int ops = ssc.validOps();
        selector = Selector.open();
        ssc.register(selector, SelectionKey.OP_ACCEPT);
        selectionKey = ssc.register(selector, ops, null);

    }

    public void startServer() throws IOException {
        synchronized (this){
            try {
                System.out.println("Server starting on port " + this.port);
                Iterator<SelectionKey> iter;
                SelectionKey key;

                while (this.ssc.isOpen()) {
                    selector.select();
                    iter = this.selector.selectedKeys().iterator();

                    while (iter.hasNext()) {
                        key = iter.next();
                        iter.remove();
                        if (key.isAcceptable()) this.handleAccept(key);
                        if (key.isReadable()) this.handleRead(key);
                    }
                }
            } catch (IOException e) {
                System.err.println("IOException, server of port " + port + " terminating. Stack trace:");
                e.printStackTrace();
            }
    }

}

    private void handleAccept(SelectionKey key) throws IOException {
        SocketChannel sc = ((ServerSocketChannel) key.channel()).accept();
        String address = sc.socket().getInetAddress().toString() + ":" + sc.socket().getPort();
        sc.configureBlocking(false);
        sc.register(selector, SelectionKey.OP_READ, address);
        sc.write(welcomeBuf);
        welcomeBuf.rewind();
        System.out.println("accepted connection from: "+address);
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
            byteBuf.clear();
        }
        String msg;
        if(read < 0) {
            msg = key.attachment()+" has left the building\n";
            ch.close();
        }
        else {
            msg = key.attachment()+": "+ sb;
        }
        System.out.println(msg);
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
        ServerSelector server = new ServerSelector(26666);
        server.startServer();
    }
}
