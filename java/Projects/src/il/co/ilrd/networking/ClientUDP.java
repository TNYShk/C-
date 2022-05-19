package il.co.ilrd.networking;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;


public class ClientUDP {
    static String host = "192.168.68.101";
    public static void connectToServer(int port,String msg) {
        try(DatagramSocket socket = new DatagramSocket()){
            InetAddress Iadrs =InetAddress.getByName(host);
            byte[] inputBuf = new byte[512];
            byte[] outBuf = msg.getBytes();

            DatagramPacket request = new DatagramPacket(outBuf, outBuf.length , Iadrs , port);
            DatagramPacket reply = new DatagramPacket(inputBuf, inputBuf.length);

            socket.send(request);
            socket.receive(reply);

            echo(new String(inputBuf,0,reply.getLength()));

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void listenUDP(){
        int port = 10523;
        String str;
        int i = 0;

        try( BufferedReader clientInput = new BufferedReader(new InputStreamReader(System.in));
             DatagramSocket sock = new DatagramSocket()){

            InetAddress Ihost = InetAddress.getByName(host);
            echo("Enter message to send: ");

            while(i<10)
            {
                str = clientInput.readLine();

                DatagramPacket dp = new DatagramPacket(str.getBytes(), str.getBytes().length , Ihost , port);
                sock.send(dp);

                DatagramPacket reply = new DatagramPacket(new byte[1024], 1024);
                sock.receive(reply);

                byte[] answer = reply.getData();
                str = new String(answer,0, reply.getLength());
                String answerMsg = new BufferedReader(new InputStreamReader(new ByteArrayInputStream(answer))).readLine();

                if(str.equals("ping"))
                    echo("pong");

                echo(answerMsg);

                ++i;
            }
        }

        catch(IOException e)
        {
            System.err.println("IOException " + e);
        }
    }





    public static void main(String[] args) throws IOException {
        //connectToServer(25666,"ping");
        listenUDP();
    }


    public static void echo(String msg)
    {
        System.out.println(msg);
    }
}
