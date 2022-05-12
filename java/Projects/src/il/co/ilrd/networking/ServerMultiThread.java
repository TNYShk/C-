package il.co.ilrd.networking;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicInteger;

public class ServerMultiThread implements Runnable {
    protected int serverPort;
    protected ServerSocket serverSocket = null;
    protected volatile boolean isRunning;
    protected Thread runningThread = null;
    protected AtomicInteger counter = new AtomicInteger(0);
    protected ServerUDP serverUdp = null;
    public ServerMultiThread(int port) {
        serverPort = port;
        isRunning = true;
        serverUdp = new ServerUDP(port);
    }

    public void runUDP(){
        Thread udpRun = new Thread(new Runnable() {
            @Override
            public void run() {
                synchronized (this) {
                    try {
                        serverUdp.listen();
                    } catch (Exception e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        });
        udpRun.start();
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
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
            new Thread(new WorkerRunnable(clientSocket,"10.1.0.164 ")
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

           try( Scanner input  = new Scanner(clientSocket.getInputStream());
                OutputStream output = clientSocket.getOutputStream();
               PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)) {
               output.write(("Greetings!! from the underworld\nWorkerRunnable: " + this.serverText + " - ").getBytes());
               counter.getAndIncrement();
               out.println("greetings user: " + counter);
               while (isRunning) {
                   String msg = input.nextLine();
                   output.write(("מקלידה כפרעעע").getBytes());
                   System.out.println("Request processed: " + msg);
               }

            }catch(IOException e){
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args){
        ServerMultiThread server = new ServerMultiThread(26666);
        new Thread(server).start();
        server.runUDP();
      /*try {
            Thread.sleep(20 * 1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Stopping Server");
        server.stop();*/

    }
}
