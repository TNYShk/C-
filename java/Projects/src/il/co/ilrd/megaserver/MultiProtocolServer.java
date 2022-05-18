package il.co.ilrd.megaserver;

import org.omg.PortableInterceptor.ORBInitInfoPackage.DuplicateName;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.*;
import java.util.concurrent.TimeUnit;

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
        if(port < 1 || port > 65000)
            throw new IllegalArgumentException();
        connectHandler.addTCP(port);
    }

    public void addUDP(int port) throws IOException {
        if(port < 1 || port > 65000)
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
        System.out.println(Thread.currentThread().getName());
    }

    public void serverDown() throws IOException {
        isRun = false;
        connectHandler.selector.close();
    }

    private class connectionHandler{
        //List<SelectionKey> tcpserverList;
       // List<SelectionKey> udpserverList;
        private Selector selector;


        public connectionHandler() throws IOException {
           // tcpserverList = new ArrayList<>();
            //udpserverList = new ArrayList<>();

            selector = Selector.open();
        }
        public void addTCP(int port) throws IOException {
            if(!portList.add(port))
                throw new IllegalArgumentException("duplicate port");

                ServerSocketChannel tcp = ServerSocketChannel.open();
                tcp.socket().bind(new InetSocketAddress(port));
                tcp.configureBlocking(false);

                tcp.register(selector, SelectionKey.OP_ACCEPT, tcp);
                System.out.println("tcp added!");
                //tcpserverList.add(sKey);

        }

        public void addUDP(int port) throws IOException {
            if(!portList.add(port))
                throw new IllegalArgumentException("duplicate port");

                DatagramChannel udp = DatagramChannel.open();
                udp.socket().bind(new InetSocketAddress(port));
                udp.configureBlocking(false);
                udp.register(selector, SelectionKey.OP_READ, udp);
                System.out.println("udp added!");
               // udpserverList.add(sKey);

        }

        public void start() throws IOException {
            selector = Selector.open();
            System.out.println(Thread.currentThread().getName());
            try {
                Iterator<SelectionKey> iter;
                SelectionKey key;
                while (isRun) {
                    selector.select();

                    iter = selector.selectedKeys().iterator();

                    while (iter.hasNext()) {
                        key = iter.next();

                        if (key.attachment() instanceof DatagramChannel) {
                            UDPCommunicator udpConnect = new UDPCommunicator();
                            udpConnect.handle(key);

                        }
                        else {
                            if (key.isAcceptable()) {
                                ServerSocketChannel ssChannel = (ServerSocketChannel)key.attachment();
                                System.out.println("here");
                                acceptConnectionTCP tcpAccept = new acceptConnectionTCP(ssChannel);
                                tcpAccept.handle(key);
                            } else if (key.isReadable()) {
                                TCPCommunicator tcpConnect = new TCPCommunicator();
                                System.out.println("there");
                                tcpConnect.handle(key);
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
        private final ByteBuffer welcomeBuf = ByteBuffer.wrap("TCP communicator handler\n".getBytes());
        private ServerSocketChannel serverSocketChannel;

        public acceptConnectionTCP(ServerSocketChannel serverSocketChannel) {
            super();
            this.serverSocketChannel = serverSocketChannel;
        }

        @Override
        public void handle(SelectionKey key) {
            try {
                SocketChannel client = serverSocketChannel.accept();
                String address = client.socket().getInetAddress().toString() + ":" + client.socket().getPort();
                client.configureBlocking(false);
                client.register(selector, SelectionKey.OP_READ | SelectionKey.OP_ACCEPT);
                System.out.println("accepted connection from: " + address);
                client.write(welcomeBuf);
                welcomeBuf.rewind();
                System.out.println("done with the handle");
            } catch (IOException e) {
                e.printStackTrace();
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
                throw new RuntimeException();
            }
        }

            @Override
            public void send(ByteBuffer buffer) {
                try {
                    buffer.rewind();
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

            public UDPCommunicator(){
                buffer = ByteBuffer.allocate(1024);
            }

            @Override
            public void handle(SelectionKey key) {
                try {
                    client = (DatagramChannel) key.channel();
                    socketAdrsUDP = client.receive(buffer);
                    buffer.flip();
                    msgHandler.handleMessage(buffer, this);
                }catch(IOException | ClassNotFoundException e){
                    System.err.println(e);
                }
            }

            @Override
            public void send(ByteBuffer buffer) {
                try {
                    client.send(buffer, socketAdrsUDP);
                }catch(IOException e){
                    System.err.println(e);
                }
                finally {
                    buffer.clear();
                }
            }
        }
    }

        private class MessageHandler implements SerializeIt{
            private Map<ServerProtocol,Protocol> serverProtocol;


            public MessageHandler(){
                serverProtocol = new HashMap<>();
                serverProtocol.put(ServerProtocol.PINGPONG, new PingPong());
               // serverProtocol.put(ServerProtocol.CHAT, new Chat());

            }
            // can pass id instead of connection..
            public void handleMessage(ByteBuffer buffer, connectionHandler.ConnectionCommunicator connection) throws IOException, ClassNotFoundException {


                Object object = deserialize(buffer);
                if (!(object instanceof ServerMessage)) {
                    throw new ClassCastException();
                }
                ServerMessage serverMessage = (ServerMessage)object;
                Protocol protocol = serverProtocol.get(serverMessage.getKey());
                protocol.action(serverMessage.getData(),connection);
            }
            @Override
            public Object deserialize(ByteBuffer buffer) throws IOException, ClassNotFoundException {
                try (ObjectInputStream objOIS = new ObjectInputStream(new ByteArrayInputStream(buffer.array()))) {
                        return objOIS.readObject();
                    }
            }
            @Override
            public ByteBuffer serialize(Object serverMsg) throws IOException {
                try(ByteArrayOutputStream bos = new ByteArrayOutputStream();
                    ObjectOutputStream oos = new ObjectOutputStream(bos)) {
                        oos.writeObject(serverMsg);
                        oos.flush();
                        return ByteBuffer.wrap(bos.toByteArray());
                    }
            }





            private abstract class Protocol {
                public abstract void action(Message<?, ?> msg, connectionHandler.ConnectionCommunicator connect);
            }

            private class PingPong extends Protocol {


                @Override
                public void action(Message<?, ?> msg, connectionHandler.ConnectionCommunicator connect )  {
                    if (!(msg instanceof PingPongMessage)) {
                        throw new ClassCastException();
                    }

                    PingPongKeys key = (PingPongKeys)msg.getKey();
                    System.out.println("in pingpong class " + key);
                    //PingPongMessage replyb = new PingPongMessage(key.reply());
                    ServerMessage servermessage = new ServerMessage(ServerProtocol.PINGPONG,new PingPongMessage(key.reply()));
                    try{
                        ByteBuffer temp = serialize(servermessage);

                        connect.send(temp);
                    }catch (IOException e){
                        e.printStackTrace();
                    }

                }
            }
        }


    public static void main(String[] args) throws IOException, InterruptedException {
        MultiProtocolServer testS = new MultiProtocolServer();
        testS.addTCP(10523);
        testS.serverUp();
        TimeUnit.SECONDS.sleep(10);

        }
    }



