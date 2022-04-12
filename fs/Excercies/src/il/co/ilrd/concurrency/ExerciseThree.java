package il.co.ilrd.concurrency;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

import static java.lang.Thread.sleep;


public class ExerciseThree {
    BlockingQueue<Double> blockingQueue = new LinkedBlockingDeque<>(5);

    private void produce() {
        while (true) {
            double value = generateValue();
            try {
                blockingQueue.put(value);
            } catch (InterruptedException e) {
                e.printStackTrace();
                break;
            }
            System.out.printf("[%s] Value produced: %f\n", Thread.currentThread().getName(), value);
        }
    }

    private void consume() {
        while (true) {
            Double value;
            try {
                value = blockingQueue.take();
            } catch (InterruptedException e) {
                e.printStackTrace();
                break;
            }
            // Consume value
            System.out.printf("[%s] Value consumed: %f\n", Thread.currentThread().getName(), value);
        }
    }

    private double generateValue() {
        return Math.random();
    }

    private void runProducerConsumer() {
        for (int i = 0; i < 2; i++) {
            Thread producerThread = new Thread(this::produce);
            producerThread.start();
        }

        for (int i = 0; i < 3; i++) {
            Thread consumerThread = new Thread(this::consume);
            consumerThread.start();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        ExerciseThree simpleProducerConsumerDemonstrator = new ExerciseThree();
        simpleProducerConsumerDemonstrator.runProducerConsumer();
        Thread.sleep(2000);
        System.exit(0);
    }


}

class Message{
    private  int id;
    private double data;

    public Message(int id, double data){
        this.id = id;
        this.data = data;
    }
    public int getId(){
        return id;
    }
    public void setId(int id){
        this.id = id;
    }

    public double getData(){
        return data;
    }

    public void setData(double data){
        this.data = data;
    }

}

class DataQueue{
    private final Queue<Message> qQ = new LinkedList<>();
    private final int maxSize;
    private final Object FULL_QUEUE = new Object();
    private final Object EMPTY_QUEUE = new Object();

    public DataQueue(int maxSize) {
        this.maxSize = maxSize;
    }

    public boolean isFull() {
        return qQ.size() == maxSize;
    }

    public boolean isEmpty() {
        return qQ.isEmpty();
    }

    public void waitOnFull() throws  InterruptedException{
        synchronized (FULL_QUEUE){
            FULL_QUEUE.wait();
        }
    }
    public void notifyAllisFull(){
        synchronized (FULL_QUEUE){
            FULL_QUEUE.notify();
        }
    }

    public void waitOnEmpty() throws InterruptedException{
        synchronized (EMPTY_QUEUE){
            EMPTY_QUEUE.wait();
        }
    }

    public void notifyAllisEmpty(){
        synchronized (EMPTY_QUEUE){
            EMPTY_QUEUE.notify();
        }
    }

    public void add(Message text){
        synchronized (qQ){
            qQ.add(text);
        }
    }

    public Message remove(){
        synchronized (qQ){
            return qQ.poll();
        }
    }
}

 class Producer implements Runnable{
    private final DataQueue dataQueue;
    private volatile boolean runFlag;

    private static int idSequence = 0;

    public Producer(DataQueue dataQueue) {
        this.dataQueue = dataQueue;
        runFlag = true;
    }

    @Override
    public void run() {
        try {
            produce();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void produce() throws InterruptedException {
        while(runFlag){
            Message msg = generateMessage();
            while(dataQueue.isFull()){
                try{
                    dataQueue.waitOnFull();
                }catch (InterruptedException e){
                    e.printStackTrace();
                    break;
                }
            }
            if(!runFlag){
                break;
            }
            dataQueue.add(msg);
            dataQueue.notifyAllisEmpty();
        }
        System.out.println("producer is done");
    }

    private Message generateMessage() throws InterruptedException {
        Message message = new Message(++idSequence, (Math.random()));
        System.out.printf("[%s] Generated Message. Id: %d, Data: %f\n", Thread.currentThread().getName(), message.getId(), message.getData());
        sleep(1000);
        return message;
    }

    public void stop(){
        runFlag = false;
        dataQueue.notifyAllisFull();
    }

}
class Consumer implements Runnable{
    private final DataQueue dataQueue;
    private volatile boolean runFlag;

    public Consumer(DataQueue dataQueue) {
        this.dataQueue = dataQueue;
        runFlag = true;
    }

    @Override
    public void run() {
        try {
            consume();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void consume() throws InterruptedException {
        while (runFlag) {
            Message message;
            if (dataQueue.isEmpty()) {
                try {
                    dataQueue.waitOnEmpty();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
            if (!runFlag) {
                break;
            }
            message = dataQueue.remove();
            dataQueue.notifyAllisFull();
            useMessage(message);
        }
        System.out.println("Consumer Stopped");
    }
    private void useMessage(Message message) throws InterruptedException {
        if (message != null) {
            System.out.printf("[%s] Consuming Message. Id: %d, Data: %f\n", Thread.currentThread().getName(), message.getId(), message.getData());

            //Sleeping on random time to make it realistic
            sleep(1500);
        }
    }

    public void stop() {
        runFlag = false;
        dataQueue.notifyAllisEmpty();
    }
}

