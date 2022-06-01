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

           for(int i =0; i<10;++i){
              // System.out.println("pong");
                String out = reader.readLine();
                //System.out.println(out);
                System.out.println("msg from server: "+out);
                if(out.equals("ping"))
                    writer.println("pong");
                else
                 writer.println(out);
           }

       } catch (IOException ex) {
           System.out.println("Server not found: " + ex.getMessage());
       }
   }
    public static void main(String[] args) {
      // connectToServer("10.111.0.10",26666);
        //connectToServer("10.1.0.116",12212);
       // connectToServer("10.10.1.32",50001);
        //connectToServer("10.10.1.116",10523);
        connectToServer("localhost",10523);
    }

}
