package il.co.ilrd.megaserver;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.util.*;

public class MultiProtocolServer {

    private connectionHandler connectHandler;
    private MessageHandler msgHandler;

    public MultiProtocolServer(connectionHandler connectHandler, MessageHandler msgHandler) {
        this.connectHandler = connectHandler;
        this.msgHandler = msgHandler;
    }


    public void addTCP(int port) throws IOException {
        new connectionHandler().addTCP(port);
    }

    public void addUDP(int port) throws IOException {
        new connectionHandler().addUDP(port);
    }

    public void serverUp(){}

    public void serverDown(){}

    private class connectionHandler{
        List<ServerSocketChannel> tcpserverList;
        List<DatagramChannel> udpserver;
        private Selector selector;

        public connectionHandler() throws IOException {
            tcpserverList = new ArrayList<>();
            udpserver = new ArrayList<>();
            selector = Selector.open();
        }
        public void addTCP(int port) throws IOException {
            ServerSocketChannel tcp = ServerSocketChannel.open();
            tcp.socket().bind(new InetSocketAddress(port));
            tcp.configureBlocking(false);
            int ops = tcp.validOps();

            tcp.register(selector,SelectionKey.OP_ACCEPT);
            tcpserverList.add(tcp);
            SelectionKey sKey = tcp.register(selector,ops,null);
        }

        public void addUDP(int port) throws IOException {
            DatagramChannel udp = DatagramChannel.open();
            udp.socket().bind(new InetSocketAddress(port));
            udp.configureBlocking(false);
            udp.register(selector,SelectionKey.OP_READ);
            udpserver.add(udp);
        }

        public void start(){}

        private abstract class Connection{
                // need to pass key?
        public abstract void handle(SelectionKey key);
        }

            private abstract class ConnectionCommunicator extends Connection {
                public abstract void send(ByteBuffer buffer);
            }

            private class acceptConnectionTCP extends Connection {

                @Override
                public void handle(SelectionKey key) {
                    // TODO Auto-generated method stub

                }

            }
        private class TCPCommunicator extends ConnectionCommunicator {

            @Override
            public void handle(SelectionKey key) {
                // TODO Auto-generated method stub

            }

            @Override
            public void send(ByteBuffer buffer) {
                // TODO Auto-generated method stub

            }

        }

        private class UDPCommunicator extends ConnectionCommunicator {

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
            // map key = serverProtocol,  value = Protocol
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



