package il.co.ilrd.networking;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class ClientBroadcast {
    public static void main(String[] args) throws IOException {
        int port = 51666;
        int i = 0;
        byte[] test = "נו זה כמו מו".getBytes();

            try(DatagramSocket sock = new DatagramSocket()) {
                InetAddress host = InetAddress.getByName("255.255.255.255");
                sock.setBroadcast(true);

                while (i < 10) {


                    DatagramPacket dp = new DatagramPacket(test, test.length, host, port);
                    sock.send(dp);

                    DatagramPacket reply = new DatagramPacket(new byte[1024], 1024);
                    sock.receive(reply);

                    byte[] answer = reply.getData();
                    String response;
                    response = new BufferedReader(new InputStreamReader(new ByteArrayInputStream(answer))).readLine();
                    echo(response);
                    ++i;
                }
            }

        }


    public static void echo(String msg)
    {
        System.out.println(msg);
    }
}
