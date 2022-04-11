package il.co.ilrd.concurrency;

public class ExerciseOne extends Thread{
    private volatile boolean doStop = false;

    private synchronized boolean keepRunning(){
        return (this.doStop == false);
    }
    @Override
    public void run() {
        while (keepRunning()) {

            System.out.println("MyThread thread is running!" + java.time.LocalDateTime.now() + " " + currentThread().getName());
            try {
                System.out.println("here???");
                Thread.sleep(5000);
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
            return this.pleaseStop == false;
        }

        @Override
        public void run() {
            while(keepRunning()){
                System.out.println("Run Forest Run!");

                try{
                    Thread.sleep(3L * 3000L);
                } catch (InterruptedException e){
                    e.printStackTrace();
                }
                System.out.println("done running");
                doStop();
            }
        }
    }


    public static void main(String args[]) throws InterruptedException {
        //ExerciseOne.Ex1();
   /*     ExerciseOne outside = new ExerciseOne();
        runRunRun inner = outside.new runRunRun();
       inner.run();
        System.out.println("in main");*/

        ExerciseTwo next = new ExerciseTwo();

        Thread one = new Thread(next);
        Thread two = new Thread(next);

        one.start();
        two.start();
        one.join();
        two.join();
        //System.out.println("counter "+ ExerciseTwo.globalCounter);

    }

}


