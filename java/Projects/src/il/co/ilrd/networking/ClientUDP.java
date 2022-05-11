package il.co.ilrd.networking;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class ClientUDP {


    public static void main(String[] args) {
        int port = 7878;
        String str;
        int i = 0;
        Scanner in = new Scanner(System.in);
       try( BufferedReader clientInput = new BufferedReader(new InputStreamReader(System.in))){

           DatagramSocket sock = new DatagramSocket();
           InetAddress host = InetAddress.getByName("localhost");
           echo("Enter message to send: ");

            while(i<10)
            {
                str = clientInput.readLine();
                byte[] b = str.getBytes();

                DatagramPacket  dp = new DatagramPacket(b , b.length , host , port);
                sock.send(dp);


                byte[] buffer = new byte[100];
                DatagramPacket reply = new DatagramPacket(buffer, buffer.length);
                sock.receive(reply);

                byte[] data = reply.getData();
                str = new String(data, 0, reply.getLength());

                if(str.equals("ping"))
                    echo("pong");

                ++i;
            }
            sock.close();
        }

        catch(IOException e)
        {
            System.err.println("IOException " + e);
        }
    }

    //simple function to echo data to terminal
    public static void echo(String msg)
    {
        System.out.println(msg);
    }
}

 /*private DatagramSocket udpSocket;
    private String ping = "ping";
    private String s;
    private int port;
    //private Scanner scanner;

    public ClientUDP(int port) throws IOException{

        this.port = port;

        try(BufferedReader clientInput = new BufferedReader(new InputStreamReader(System.in))) {
            udpSocket = new DatagramSocket(port);
            InetAddress host = InetAddress.getByName("localhost");
            while (true) {
                s = clientInput.readLine();
                byte[] data = s.getBytes();
                DatagramPacket dp = new DatagramPacket(data, data.length, host, port);
                udpSocket.send(dp);

                byte[] buffer = new byte[100];
                DatagramPacket reply = new DatagramPacket(buffer, buffer.length);
                udpSocket.receive(reply);

                byte[] d = reply.getData();
                s = new String(d, 0, reply.getLength());
                echo(reply.getAddress().getHostAddress() + " : " + reply.getPort() + " - " + s);
            }
        }

    }
*/