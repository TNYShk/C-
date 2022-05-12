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
    protected int UDPport;

    protected ServerSocket serverSocket = null;
    protected volatile boolean isRunning;
    protected Thread runningThread = null;
    protected Thread udpThread = null;
    protected Thread broadcatUDP = null;
    protected AtomicInteger counter = new AtomicInteger(0);
    protected ServerUDP serverUdp = null;
    protected ServerBroadcast broadcast = null;
    public ServerMultiThread(int port, int udport) {
        serverPort = port;
        isRunning = true;
        UDPport = udport;
    }

    public void runUDP(){
        udpThread = new Thread(new Runnable() {
            @Override
            public void run() {
                synchronized (this) {
                    try {
                        serverUdp = new ServerUDP(UDPport);
                        serverUdp.listen();
                        new Thread(() -> broadway());
                    } catch (Exception e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        });
        udpThread.start();
    }

    public void broadway(){
        broadcatUDP = new Thread(new Runnable() {
            @Override
            public void run() {
                synchronized (this) {
                    try {
                        broadcast = new ServerBroadcast();

                    } catch (Exception e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        });
        broadcatUDP.start();
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
            new Thread(new WorkerRunnable(clientSocket,"10.111.0.10")
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
            throw new RuntimeException("Cannot open port ", e);
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
        ServerMultiThread server = new ServerMultiThread(26666,25666);
        new Thread(server).start();

        server.runUDP();

      try {
            Thread.sleep(20 * 1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Stopping Server");
        server.stop();

    }
}
