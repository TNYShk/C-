package il.co.ilrd.multiserverprotocol;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.*;

public class MultiProtocolServer {
    private connectionHandler connectHandler;
    private MessageHandler msgHandler;
    private Set<Integer> portList;
     private volatile boolean isRun;
    protected Selector selector;


    public MultiProtocolServer() throws IOException {
        connectHandler = new connectionHandler();
        msgHandler = new MessageHandler();
        portList = new HashSet<>();
        selector = Selector.open();
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

    }

    public void serverDown() throws IOException {
        isRun = false;
        selector.close();
    }

    private class connectionHandler{
        UDPCommunicator udpConnect;

        public void addTCP(int port) throws IOException {
            if(!portList.add(port))
                throw new IllegalArgumentException("duplicate port");

            ServerSocketChannel tcp = ServerSocketChannel.open();
            tcp.socket().bind(new InetSocketAddress(port));
            tcp.configureBlocking(false);
            acceptConnectionTCP tcpAccept = new acceptConnectionTCP(tcp);
            SelectionKey key = tcp.register(selector, SelectionKey.OP_ACCEPT, tcp);
            key.attach(tcpAccept);

            System.out.println("tcp added!");

        }

        public void addUDP(int port) throws IOException {
            if(!portList.add(port))
                throw new IllegalArgumentException("duplicate port");

            DatagramChannel udp = DatagramChannel.open();
            udp.socket().bind(new InetSocketAddress(port));
            udp.configureBlocking(false);
            udp.register(selector, SelectionKey.OP_READ, udp);
            System.out.println("udp added!");
             udpConnect = new UDPCommunicator();


        }

        public void start() throws IOException {

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
                            udpConnect.handle(key);
                        }
                        else {
                            if (key.isAcceptable()) {
                                ((acceptConnectionTCP)key.attachment()).handle(key);

                            } else if (key.isReadable()) {
                                ((ConnectionCommunicator)key.attachment()).handle(key);
                            }
                        }
                        iter.remove();
                    }
                }
            }catch (IOException e){
                throw new RuntimeException(e);
            }
        }

        private abstract class Connection{
            public abstract void handle(SelectionKey key);
        }

        private abstract class ConnectionCommunicator extends Connection {
            public abstract void send(ByteBuffer buffer);
        }

    private class acceptConnectionTCP extends Connection {
        private ServerSocketChannel serverSocketChannel;
        public acceptConnectionTCP(ServerSocketChannel serverSocketChannel) {
            //super();
            this.serverSocketChannel = serverSocketChannel;
        }
        @Override
        public void handle(SelectionKey key) {
            try {
                SocketChannel client = serverSocketChannel.accept();
                String address = client.socket().getInetAddress().toString() + ":" + client.socket().getPort();
                client.configureBlocking(false);
                TCPCommunicator tcpConnect = new TCPCommunicator(client);

                System.out.println("accepted connection from: " + address);
                SelectionKey tcpKey = client.register(selector, SelectionKey.OP_READ);
                tcpKey.attach(tcpConnect);

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
        private class TCPCommunicator extends ConnectionCommunicator {
            private SocketChannel client;

            public TCPCommunicator(SocketChannel client) {
                this.client = client;
            }

            @Override
        public void handle(SelectionKey key) {
                client = (SocketChannel) key.channel();
            try {
                ByteBuffer tmp = ByteBuffer.allocate(8192);
                if(-1 == client.read(tmp)){
                    client.close();
                    return;
                }

                msgHandler.handleMessage(tmp,this);

            }catch(IOException | ClassNotFoundException e){

               System.err.print(e);
            }
        }

            @Override
            public void send(ByteBuffer buffer) {
                try {
                    client.write(buffer);
                    buffer.clear();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        private class UDPCommunicator extends ConnectionCommunicator {
            private DatagramChannel client;
            private ByteBuffer UDbuffer;
            private SocketAddress socketAdrsUDP;

            public UDPCommunicator(){
                UDbuffer = ByteBuffer.allocate(8192);
            }

            @Override
            public void handle(SelectionKey key) {
                try {
                    client = (DatagramChannel) key.channel();
                    socketAdrsUDP = client.receive(UDbuffer);
                    UDbuffer.flip();
                    msgHandler.handleMessage(UDbuffer, this);
                }catch(IOException | ClassNotFoundException e){
                    System.err.println(e);
                }
            }

            @Override
            public void send(ByteBuffer buffer) {
                try {
                    //buffer.flip();
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
            private final Map<ServerProtocol,Protocol> serverProtocolMap;
            private connectionHandler.ConnectionCommunicator connection;
            public MessageHandler(){
                serverProtocolMap = new HashMap<>();
                serverProtocolMap.put(ServerProtocol.PINGPONG, new PingPong());
                serverProtocolMap.put(ServerProtocol.CHAT, new Chat());

            }

            public void handleMessage(ByteBuffer buffer, connectionHandler.ConnectionCommunicator connection) throws IOException, ClassNotFoundException {
               this.connection = connection;
                buffer.flip();
                Object object = deserialize(buffer);
                if(object.toString().equals("ServerMessage")){
                    ServerMessage serverMessage = (ServerMessage)object;
                    Protocol protocol = serverProtocolMap.get(serverMessage.getKey());
                    protocol.action(serverMessage.getData());
                }else{
                    System.out.println("im here error");
                    ServerMessage errMsg = new ServerMessage(ServerProtocol.ERROR_SERVER_PROTOCOL, null);
                    connection.send(serialize(errMsg));
                }


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
                public abstract void action(Message<?, ?> msg);
            }
            private class Chat extends Protocol {
                private HashSet<connectionHandler.ConnectionCommunicator> chatClient = new HashSet<>();
                private ByteBuffer bufferChat = ByteBuffer.allocate(8192);

                @Override
                public void action(Message<?, ?> msg )  {
                    if(msg.toString().equals("ChatMessage")) {

                        ChatKeys key = (ChatKeys) msg.getKey();
                        String msgg = (String) msg.getData();

                        if (key.equals(ChatKeys.REGISTER)) {
                            chatClient.add(connection);
                            craftMsg(ChatKeys.PUBLISH, "welcome! " + msgg);
                        } else if (key.equals(ChatKeys.UNREGISTER)) {
                            chatClient.remove(connection);
                            craftMsg(ChatKeys.PUBLISH, "good bye!");
                        } else if (key.equals(ChatKeys.BROADCAST)) {
                            for (connectionHandler.ConnectionCommunicator c : chatClient)
                                craftMsg(ChatKeys.PUBLISH, c.toString() + " : "+ msgg);
                        }
                        else{
                            craftMsg(ChatKeys.ERROR_CHAT_KEYS, "ERROR");
                        }
                    }
                }

                private void craftMsg(ChatKeys key, String msg){
                    ChatMessage servermessage = new ChatMessage(key, msg);

                    try{
                        connection.send(serialize(servermessage));
                    }catch (IOException e){
                        e.printStackTrace();
                    }
                }
            }
            private class PingPong extends Protocol {

                @Override
                public void action(Message<?, ?> msg)  {
                    if (!(msg instanceof PingPongMessage)) {
                        throw new ClassCastException();
                    }

                    PingPongKeys key = (PingPongKeys)msg.getKey();
                    System.out.println("server received " + key);
                    key = key.reply();

                    ServerMessage servermessage = new ServerMessage(ServerProtocol.PINGPONG, new PingPongMessage(key));
                    ByteBuffer temp;
                    try{
                        temp = serialize(servermessage);
                        System.out.println("server sending data " + servermessage.getData());

                        connection.send(temp);

                    }catch (IOException e){
                        e.printStackTrace();
                    }
                }
            }
        }


    public static void main(String[] args) throws IOException, InterruptedException {
        MultiProtocolServer testS = new MultiProtocolServer();
        testS.addTCP(10523);
        testS.addUDP(10521);
        testS.serverUp();
       /* TimeUnit.SECONDS.sleep(4);
        testS.serverDown();*/

        }
    }



