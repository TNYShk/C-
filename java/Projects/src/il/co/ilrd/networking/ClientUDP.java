package il.co.ilrd.networking;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class ClientUDP {


    public static void main(String[] args) throws IOException {
        int port = 10523;
        String str;
        int i = 0;

       try( BufferedReader clientInput = new BufferedReader(new InputStreamReader(System.in));
            DatagramSocket sock = new DatagramSocket()){

           InetAddress host = InetAddress.getByName("192.168.68.101");
           echo("Enter message to send: ");

            while(i<10)
            {
                str = clientInput.readLine();

                DatagramPacket  dp = new DatagramPacket(str.getBytes(), str.getBytes().length , host , port);
                sock.send(dp);

                byte[] buffer = new byte[1024];
                DatagramPacket reply = new DatagramPacket(buffer, buffer.length);
                sock.receive(reply);

                byte[] data = reply.getData();
                str = new String(data, 0, reply.getLength());

                if(str.equals("ping"))
                    echo("כפרעעעע");

                ++i;
            }
        }

        catch(IOException e)
        {
            System.err.println("IOException " + e);
        }
    }


    public static void echo(String msg)
    {
        System.out.println(msg);
    }
}
