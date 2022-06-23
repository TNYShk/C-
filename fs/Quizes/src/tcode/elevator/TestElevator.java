package tcode.elevator;

public class TestElevator {

    public static void main(String[] args){
        Elevator elevator = new Elevator();

        ProcessJobWorker processJobWorker = new ProcessJobWorker(elevator);
        Thread t1 = new Thread(processJobWorker);
        t1.start();
        try{
            Thread.sleep(300);
        } catch(InterruptedException e){
            e.printStackTrace();
        }

        ExternalButton extPush = new ExternalButton(Direction.DOWN, 5);
        InternalButton intPush = new InternalButton(0);

        Request req1 = new Request(intPush,extPush);
        new Thread(new AddJobWorker(elevator,req1)).start();
    }
}
