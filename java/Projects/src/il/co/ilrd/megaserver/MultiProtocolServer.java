package il.co.ilrd.megaserver;

import org.omg.PortableInterceptor.ORBInitInfoPackage.DuplicateName;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.*;

public class MultiProtocolServer {
    private connectionHandler connectHandler;
    private MessageHandler msgHandler;
    private Set<Integer> portList;
     private volatile boolean isRun;

    public MultiProtocolServer() throws IOException {
        connectHandler = new connectionHandler();
        msgHandler = new MessageHandler();
        portList = new HashSet<>();
    }


    public void addTCP(int port) throws IOException {
        if(port < 0 || port > 60000)
            throw new IllegalArgumentException();
        connectHandler.addTCP(port);
    }

    public void addUDP(int port) throws IOException {
        if(port < 0 || port > 60000)
            throw new IllegalArgumentException();
        connectHandler.addUDP(port);
    }

    public void serverUp(){
        isRun = true;
        Thread srvrUpper = new Thread(() -> {
            try {
                connectHandler.start();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });
        srvrUpper.start();
    }

    public void serverDown() throws IOException {
        connectHandler.selector.close();
    }

    private class connectionHandler{
        List<SelectionKey> tcpserverList;
        List<SelectionKey> udpserverList;
        private Selector selector;


        public connectionHandler() throws IOException {
            tcpserverList = new ArrayList<>();
            udpserverList = new ArrayList<>();

            selector = Selector.open();
        }
        public void addTCP(int port) throws IOException {
            if(!portList.add(port))
                throw new IllegalArgumentException("duplicate port");
            synchronized (this) {
                ServerSocketChannel tcp = ServerSocketChannel.open();
                tcp.socket().bind(new InetSocketAddress(port));
                tcp.configureBlocking(false);

                SelectionKey sKey = tcp.register(selector, SelectionKey.OP_ACCEPT, tcp);

                tcpserverList.add(sKey);
            }
        }

        public void addUDP(int port) throws IOException {
            if(!portList.add(port))
                throw new IllegalArgumentException("duplicate port");
            synchronized (this) {
                DatagramChannel udp = DatagramChannel.open();
                udp.socket().bind(new InetSocketAddress(port));
                udp.configureBlocking(false);
                SelectionKey sKey = udp.register(selector, SelectionKey.OP_READ, udp);

                udpserverList.add(sKey);
            }
        }

        public void start() throws IOException {
            selector = Selector.open();
            try {
                Iterator<SelectionKey> iter;
                SelectionKey key;
                while (isRun) {
                    selector.select();

                    iter = selector.selectedKeys().iterator();

                    while (iter.hasNext()) {
                        key = iter.next();

                        if (key.attachment() instanceof DatagramChannel) {
                            UDPCommunicator udpConect = new UDPCommunicator();
                            udpConect.handle(key);

                        }
                        else {
                            if (key.isAcceptable()) {
                                ServerSocketChannel ssChannel = (ServerSocketChannel)key.attachment();
                                acceptConnectionTCP tcpAccept = new acceptConnectionTCP(ssChannel);
                                tcpAccept.handle(key);
                            } else if (key.isReadable()) {
                                TCPCommunicator tcpConect = new TCPCommunicator();
                                tcpConect.handle(key);
                            }

                        }
                    iter.remove();
                    }
                }
            }catch (IOException e){
                throw new RuntimeException(e);
            }
        }

        private abstract class Connection{    // need to pass key?
            public abstract void handle(SelectionKey key);
        }

        private abstract class ConnectionCommunicator extends Connection {
            public abstract void send(ByteBuffer buffer);
        }

    private class acceptConnectionTCP extends Connection {
        private SocketChannel client;
        private final ByteBuffer welcomeBuf = ByteBuffer.wrap("TCP communicator handler\n".getBytes());
        private ServerSocketChannel serverSocketChannel;

        public acceptConnectionTCP(ServerSocketChannel serverSocketChannel) {
            super();
            this.serverSocketChannel = serverSocketChannel;
        }


        @Override
        public void handle(SelectionKey key) {
            try {
                client = ((ServerSocketChannel) key.channel()).accept();
                String address = client.socket().getInetAddress().toString() + ":" + client.socket().getPort();
                client.configureBlocking(false);
                client.register(selector, SelectionKey.OP_READ, address);
                client.write(welcomeBuf);
                welcomeBuf.rewind();
                System.out.println("accepted connection from: " + address);

            } catch (ClosedChannelException e) {
                throw new RuntimeException(e);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

        }
    }
        private class TCPCommunicator extends ConnectionCommunicator {
            private SocketChannel client;
            private ByteBuffer buffer;


            public TCPCommunicator(){
                buffer = ByteBuffer.allocate(1024);
            }
            @Override
        public void handle(SelectionKey key) {
            try {
                client = (SocketChannel) key.channel();
                client.read(buffer);
                buffer.flip();

            }catch(IOException e){
               System.err.println(e);
                throw new RuntimeException();
            }
        }

            @Override
            public void send(ByteBuffer buffer) {
                try {
                    //buffer.rewind();
                    client.write(buffer);
                    buffer.clear();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        private class UDPCommunicator extends ConnectionCommunicator {

            private DatagramChannel client;
            private ByteBuffer buffer;
            private SocketAddress socketAdrsUDP;

            @Override
            public void handle(SelectionKey key) {
                // TODO Auto-generated method stub
            }

            @Override
            public void send(ByteBuffer buffer) {
                // TODO Auto-generated method stub

            }

            }
        }

        private class MessageHandler{
            Map<ServerProtocol,Protocol> serverProtocol;

            public MessageHandler(){
                serverProtocol = new HashMap<>();
            }
            // can pass id instead of connection..
            public void handleMessage(ByteBuffer buffer, connectionHandler.Connection connection) {}

            private abstract class Protocol {
                public abstract void action(Message<?, ?> msg);
            }

            private class PingPong extends Protocol {

                @Override
                public void action(Message<?, ?> msg) {
                    // TODO Auto-generated method stub

                }
            }

        }
    }



