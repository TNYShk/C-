package il.co.ilrd.executor;

import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;

public class Ex2 {

    public static void SingleThreadExec(){
        ExecutorService execPool = Executors.newSingleThreadExecutor();
        execPool.execute(() -> System.out.println("hi! " + Thread.currentThread().getName() + "\n"));
        execPool.execute(() -> System.out.println("my " + Thread.currentThread().getName() + "\n"));
        execPool.execute(() -> System.out.println("name " + Thread.currentThread().getName() + "\n"));
        execPool.execute(() -> System.out.println("is " + Thread.currentThread().getName() + "\n"));

        execPool.shutdown();
    }


    public static void FixedThreadPool() throws ExecutionException, InterruptedException {
        ExecutorService singleServer = Executors.newFixedThreadPool(3);
        Future<Long> future = singleServer.submit(() -> {
            long sum = 0;
            for(long i =0; i<= 10000000l; ++i){
                sum += i;
            }
            return sum;
        });
        Future<String> texts;
        texts = singleServer.submit(() -> "Good Morning!");
        texts = singleServer.submit(() -> "Have a good Day!");
        Long result = future.get();
        System.out.println(result);
        String another = texts.get();
        String that = texts.get();
        System.out.println("string: " + another);
        System.out.println("string: " + that);
        singleServer.shutdown();

    }
    public static void main(String[] args) throws ExecutionException, InterruptedException {
        //SingleThreadExec();
        FixedThreadPool();
    }
}
