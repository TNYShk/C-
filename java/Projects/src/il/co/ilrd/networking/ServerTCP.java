package il.co.ilrd.networking;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerTCP {

    private OutputStream output;
    private InputStream input;
    private int port;
    private volatile boolean isRun;
    private Socket socket;
    public ServerTCP(int port) {
        this.port = port;
        isRun = true;
    }

    public void listenToClient() throws IOException {


        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server is listening on port " + port);
            socket = serverSocket.accept();

            System.out.println("someone's here??");

            while (isRun) {
                input = socket.getInputStream();
                output = socket.getOutputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(input));
                PrintWriter writer = new PrintWriter(new OutputStreamWriter(output), true);

                //System.out.println("ping");
                System.out.println("client sent: " + reader.readLine());

                String line = "ping";
                if (reader.readLine().equals(line)) {
                    System.out.println(line);
                    writer.println("pong");
                }
                writer.println("bla");
            }
        }catch(IOException e){
            e.printStackTrace();
        }
        System.out.println("bye!");
        input.close();
        output.close();
        socket.close();
    }



    public void closing()  {
        isRun = false;
        System.out.println("bye!");

    }

    public static void main(String[] args) {
        try {
            ServerTCP tennisServer = new ServerTCP(26666);

            tennisServer.listenToClient();
            tennisServer.closing();
        }catch (IOException e){
            e.printStackTrace();
        }
    }

}
