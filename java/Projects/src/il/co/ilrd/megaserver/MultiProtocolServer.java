package il.co.ilrd.megaserver;

import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.util.HashMap;
import java.util.Map;

public class MultiProtocolServer {

    private int port;



    public void addTCP(int port){
        new connectionHandler().addTCP(port);
    }

    public void addUDP(int port){
        new connectionHandler().addUDP(port);
    }

    public void serverUp(){}

    public void serverDown(){}

    private class connectionHandler{
        ServerSocketChannel tcpserver;
        DatagramChannel udpserver;
        private Selector selector;
        public void addTCP(int port){}

        public void addUDP(int port){}

        public void start(){}

        private abstract class Connection{
                // need to pass key?
        public abstract void handler(SelectionKey key);
        }

            private abstract class ConnectionCommunicator extends Connection {
                public abstract void send(ByteBuffer buffer);
            }

            private class acceptConnectionTCP extends Connection {

                @Override
                public void handler(SelectionKey key) {
                    // TODO Auto-generated method stub

                }

            }
        private class TCPCommunicator extends ConnectionCommunicator {

            @Override
            public void handler(SelectionKey key) {
                // TODO Auto-generated method stub

            }

            @Override
            public void send(ByteBuffer buffer) {
                // TODO Auto-generated method stub

            }

        }

        private class UDPCommunicator extends ConnectionCommunicator {

            @Override
            public void handler(SelectionKey key) {
                // TODO Auto-generated method stub
            }

            @Override
            public void send(ByteBuffer buffer) {
                // TODO Auto-generated method stub

            }

            }
        }

        private class MessageHandler{
            Map<ServerProtocol,Message<?,?>> serverProtocol;
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



