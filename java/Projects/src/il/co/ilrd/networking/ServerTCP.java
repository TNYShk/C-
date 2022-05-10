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

    public ServerTCP(int port) throws IOException {
        this.port = port;
        isRun = true;
    }

    public void listenToClient() throws IOException {
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server is listening on port " + port);
            socket = serverSocket.accept();

            while (isRun) {
                input = socket.getInputStream();
                output = socket.getOutputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(input));
                PrintWriter writer = new PrintWriter(output, true);

                System.out.println("ping");

                String line = "ping";
                if (reader.readLine().equals(line)) {
                    System.out.println("ping");
                    //System.out.println(line);
                    writer.println("pong");
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        socket.close();
    }

/*    public void sendDataToClient() throws IOException {
        OutputStream output = socket.getOutputStream();
        PrintWriter writer = new PrintWriter(output, true);
        writer.println("pong");
    }*/

    public void closing() throws IOException {
        isRun = false;
        System.out.println("bye!");
        //socket.close();
    }

    public static void main(String[] args) {

        try {
            ServerTCP tennisServer  = new ServerTCP(8080);

            tennisServer.listenToClient();
            tennisServer.closing();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
