package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

import static il.co.ilrd.networking.ClientUDP.echo;


public class ServerUDP {

    private int port;
    private DatagramPacket incoming;

    public ServerUDP(int port){
        this.port = port;
    }

    protected void listen() throws Exception{

        echo("Server is listening on port: "+ port+ "" + InetAddress.getLocalHost() + "--");
        try(DatagramSocket udpSocket = new DatagramSocket(port)) {

            incoming = new DatagramPacket(new byte[1024], 1024);

            String msg;
            String sendMsg = "ping";

            while (true) {
                udpSocket.receive(incoming);

                msg = new String(incoming.getData(), 0, incoming.getLength());

                DatagramPacket dp = new DatagramPacket(sendMsg.getBytes(), sendMsg.getBytes().length, incoming.getAddress(), incoming.getPort());
                udpSocket.send(dp);

                if (msg.equals("bye"))
                    break;

            }
        }
    }

    public  void setUDPserver(){
        try(DatagramSocket udpSocket = new DatagramSocket(port)) {
            byte[] inputBud = new byte[512];
            byte[] outBuf = "pong".getBytes();
            echo("Server is listening on port: "+ port+ "" + InetAddress.getLocalHost() + "--");

            DatagramPacket client = new DatagramPacket(inputBud, inputBud.length);
            udpSocket.receive(client);

            InetAddress clientAdrs = client.getAddress();
            int clientPort = client.getPort();
            String ping = "ping";
            String response = new String(inputBud,0,client.getLength());
            if(ping.equals(response)){
                DatagramPacket reply = new DatagramPacket(outBuf, outBuf.length,clientAdrs,clientPort);
                udpSocket.send(reply);
            }else
                udpSocket.send(client);

        }catch(IOException e){
            System.err.println(e);
        }

    }

    public static void main(String[] args) throws Exception {
        ServerUDP udp = new ServerUDP(10522);
        //udp.setUDPserver();
        /*ServerUDP udp = new ServerUDP(25666);*/
        udp.listen();
    }
}
