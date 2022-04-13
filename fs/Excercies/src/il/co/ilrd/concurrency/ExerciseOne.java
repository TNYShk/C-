package il.co.ilrd.concurrency;

public class ExerciseOne extends Thread{
    private volatile boolean doStop = false;

    private synchronized boolean keepRunning(){
        return (!this.doStop);
    }
    @Override
    public void run() {
        System.out.println("Run Forest Run! " + java.time.LocalDateTime.now() );
        while (keepRunning()) {

            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    public synchronized void doStop(){
        this.doStop = true;
    }

    private static void Ex1() throws InterruptedException{
        ExerciseOne test = new ExerciseOne();
        test.start();
        Thread.sleep(10000);
        test.doStop();
    }

     private class runRunRun implements Runnable{
        private volatile boolean pleaseStop = false;

        public synchronized void doStop() {
            this.pleaseStop = true;
        }

        private synchronized boolean keepRunning() {
            return !this.pleaseStop;
        }

        @Override
        public void run() {
            while(keepRunning()){

                System.out.println("MyThread thread is running! " + java.time.LocalDateTime.now() );
                try{
                    Thread.sleep( 5000L);
                } catch (InterruptedException e){
                    e.printStackTrace();
                }
                System.out.println("done running");
                doStop();
            }
        }
    }


    public static void main(String[] args)  {
        try{
            ExerciseOne.Ex1();
        }catch(InterruptedException e){
            e.printStackTrace();
        }

        ExerciseOne outside = new ExerciseOne();
        runRunRun inner = outside.new runRunRun();
        inner.run();





    }

}


