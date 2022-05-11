package il.co.ilrd.networking;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class ServerBroadcast {

    public static void main(String [] args) throws IOException {

        try(DatagramSocket socket = new DatagramSocket(44444)) {
            socket.setBroadcast(true);
            int i = 0;

            while (i < 10) {
                DatagramPacket request = new DatagramPacket(new byte[1024], 1024);
                socket.receive(request);
                byte[] answer = request.getData();
                ByteArrayInputStream bais = new ByteArrayInputStream(answer);
                InputStreamReader isr = new InputStreamReader(bais);
                BufferedReader br = new BufferedReader(isr);
                String msg = br.readLine();
                System.out.println("message from client: " + msg);

                InetAddress ch = request.getAddress();
                byte[] ans = "bla bla".getBytes();
                DatagramPacket reply = new DatagramPacket(ans, ans.length, ch, request.getPort());
                socket.send(reply);

                ++i;
            }

        }
    }
}
