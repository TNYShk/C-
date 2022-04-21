package il.co.ilrd.executor;





import java.util.concurrent.*;

public class Ex1  {

   public static void main(String[] args) throws ExecutionException, InterruptedException {
      ExecutorService execPool = Executors.newSingleThreadExecutor();
      execPool.execute(() -> System.out.println("hi! " + Thread.currentThread().getName() + "\n") );
       ExecutorService brara = Executors.newFixedThreadPool(3);
       StringBuffer toAdd = new StringBuffer("");
       Callable<StringBuffer> taskToCall = () -> {
           for(int i = 0; i< 6; ++i){
               toAdd.append("z");
               System.out.println(Thread.currentThread().getName());
           }
           return toAdd;
       };
       Callable<StringBuffer> anotherToCall = () -> {
           for(int i = 0; i< 6; ++i){
               toAdd.append("A");
               System.out.println(Thread.currentThread().getName());
           }
           return toAdd;
       };
       Future<StringBuffer> snotGet = brara.submit(taskToCall);
       Future<StringBuffer> anotherGet = brara.submit(anotherToCall);


       try{
           System.out.println(anotherGet.get());
           System.out.println(snotGet.get());
       }catch (ExecutionException | InterruptedException e){
           e.printStackTrace();
       }
       brara.shutdown();
       execPool.shutdown();

   }




}
