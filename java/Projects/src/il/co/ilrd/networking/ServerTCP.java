package il.co.ilrd.networking;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerTCP implements Runnable {


    private InputStream input;
    private int port;
    private volatile boolean isRun;
    private Socket socket;

    public ServerTCP(int port) throws IOException {
        this.port = port;
        try (ServerSocket serverSocket = new ServerSocket(port, 1)) {
            socket = serverSocket.accept();
            System.out.println("Server is listening on port " + port);

        }

    }

    public void listenToClient() throws IOException {
        try {
            while (isRun) {
                input = socket.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(input));
                String line = reader.readLine();
                System.out.println(line);
                if (line.equals("ping"))
                    sendDataToClient();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            socket.close();
        }

    }

    public void sendDataToClient() throws IOException {
        OutputStream output = socket.getOutputStream();
        PrintWriter writer = new PrintWriter(output, true);
        writer.println("pong");
    }

    public void closing() {
        isRun = false;
        //socket.close();
    }

    public static void main(String[] args) {
        ServerTCP tennisServer = null;
        try {
            tennisServer = new ServerTCP(8080);
        } catch (IOException e) {
            e.printStackTrace();
        }
        tennisServer.run();

    }

    @Override
    public void run() {
        isRun = true;
        try {
            listenToClient();
            Thread.currentThread().sleep(5000);
        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        } finally {
            closing();
        }

    }

}
