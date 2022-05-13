package il.co.ilrd.networking;

import java.io.*;
import java.net.Socket;

public class ClientTCP {

   public static void connectToServer(String hostname, int port){
       try (Socket socket = new Socket(hostname, port)) {
           InputStream input = socket.getInputStream();
           BufferedReader reader = new BufferedReader(new InputStreamReader(input));
           OutputStream output = socket.getOutputStream();
           PrintWriter writer = new PrintWriter(output, true);

           writer.println("ping");

            for (int i =0; i<10; ++i) {
                System.out.println("ping");
                String out = reader.readLine();
                System.out.println(out);
                writer.println("ping");
                //writer.println(out);
           }

       } catch (IOException ex) {
           System.out.println("Server not found: " + ex.getMessage());
       }
   }
    public static void main(String[] args) {
       connectToServer("192.168.68.101",26666);
        //connectToServer("10.1.0.116",12212);
       // connectToServer("10.10.1.32",50001);
    }

}
