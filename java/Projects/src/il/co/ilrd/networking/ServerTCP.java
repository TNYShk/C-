package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.concurrent.atomic.AtomicBoolean;

public class ServerTCP implements Runnable{
    private ClientTCP client;
    private DatagramSocket serverSocket;
    private Thread run, tick,send, receive;
    private int port;
    private AtomicBoolean isRun = new AtomicBoolean();

    public ServerTCP(int port){
        this.port = port;
        try{
            serverSocket = new DatagramSocket(port);
        }catch(SocketException e){
            e.printStackTrace();
        }
        run = new Thread(this, "server");
        run.start();
    }

    @Override
    public void run() {
        isRun.set(true);
        System.out.println("server started! " + port);
        tick();
        receive();
    }

    private void tick(){
        tick = new Thread(() -> {
            while(isRun.get()){}
        });
        tick.start();
    }

    private void receive(){
        receive = new Thread(){
            public void run(){
                while(isRun.get()){
                    byte[] data = {'p','o','n','g'};
                    DatagramPacket packet = new DatagramPacket(data, data.length);
                    try {
                        serverSocket.receive(packet);
                    }catch(IOException e) {
                        e.printStackTrace();
                    }
                    read(packet);
                }
            }
        };
        receive.start();
    }
    private void read(DatagramPacket packet) {
        String message = new String(packet.getData());
        System.out.println(message);
    }
}
