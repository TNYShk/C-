package il.co.ilrd.networking;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.util.Scanner;

public class ServerTCPThread implements Runnable {
    protected int serverPort = 8080;
    protected ServerSocket serverSocket = null;
    protected volatile boolean isRunning;
    protected Thread runningThread = null;

    public ServerTCPThread(int port) {
        serverPort = port;
        isRunning = true;
    }

    @Override
    public void run() {
        synchronized (this) {
            this.runningThread = Thread.currentThread();
        }
        openServerSocket();
        while(isRunning){
            Socket clientSocket = null;
            try{
                clientSocket = this.serverSocket.accept();

            } catch (IOException e) {
                if(!isRunning){
                    throw new RuntimeException("server stopped");
                }
                throw new RuntimeException("error signing up client",e);
            }
            new Thread(new WorkerRunnable(clientSocket,"Tanyas")
            ).start();
        }
        System.out.println("Server Stopped.") ;
    }

    public synchronized void stop(){
        this.isRunning = false;
        try {
            this.serverSocket.close();
        } catch (IOException e) {
            throw new RuntimeException("Error closing server", e);
        }
    }

    private void openServerSocket() {
        try {
            this.serverSocket = new ServerSocket(this.serverPort);
        } catch (IOException e) {
            throw new RuntimeException("Cannot open port 8080", e);
        }
    }
    class WorkerRunnable implements Runnable{
        protected Socket clientSocket = null;
        protected String serverText   = null;

        public WorkerRunnable(Socket clientSocket, String serverText) {
            this.clientSocket = clientSocket;
            this.serverText   = serverText;
        }

        @Override
        public void run() {
        try{
            Scanner input  = new Scanner(clientSocket.getInputStream());
            //OutputStream output = clientSocket.getOutputStream();
           // long time = System.currentTimeMillis();
            PrintWriter out =  new PrintWriter(clientSocket.getOutputStream(), true);
           // output.write(("Greetings!! from the underworld\n\nWorkerRunnable: " + this.serverText + " - " + time + "").getBytes());
            while (isRunning){
                String msg = input.nextLine();
                out.println("greetings");

//            output.close();
//            input.close();
                System.out.println("Request processed: " +  msg);
            }

            }catch(IOException e){
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args){
        ServerTCPThread server = new ServerTCPThread(8000);
        new Thread(server).start();
        /*try {
            Thread.sleep(20 * 1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Stopping Server");
        server.stop();*/

    }
}
