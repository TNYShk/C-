package il.co.ilrd.executor;

import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;

public class Ex2 {

    public static void SingleThreadExec(){
        ExecutorService execPool = Executors.newSingleThreadExecutor();
        execPool.execute(() -> System.out.print( Thread.currentThread().getName() + " hi! "));
        execPool.execute(() -> System.out.print(" my " ));
        execPool.execute(() -> System.out.print(" name " ));
        execPool.execute(() -> System.out.print(" is "  ));
        execPool.execute(() -> System.out.print("\tTanya "  ));
        execPool.shutdown();
    }

    public static void FixedThreadPool() throws ExecutionException, InterruptedException {
        ExecutorService singleServer = Executors.newFixedThreadPool(3);
        Future<Long> future = singleServer.submit(() -> {
            long sum = 0;
            for(long i = 0; i<= 10000000l; ++i){
                sum += i;
            }
            return sum;
        });
        Future<String> texts;
        Future<String> text;
        text = singleServer.submit(() -> Thread.currentThread().getName() + " Good Morning!");
        texts = singleServer.submit(() ->  Thread.currentThread().getName() + " Have a good Day!");
        Long result = future.get();
        System.out.println(result);
        String another = texts.get();
        String that = text.get();
        System.out.println( another);
        System.out.println( that);
        singleServer.shutdown();
    }

    public static void CachedPool() throws ExecutionException, InterruptedException {
        ExecutorService cachedPool = Executors.newCachedThreadPool();
        Future<Long> future = cachedPool.submit(() -> {
            long sum = 1l;
            for(long i = 1; i<= 101; ++i){
                sum *= i;
            }
            return sum;
        });
        Future<String> texts;
        Future<String> text;
        text = cachedPool.submit(() -> Thread.currentThread().getName() + " CachedPool!");
        texts = cachedPool.submit(() ->  Thread.currentThread().getName() + " eewwwuu!");
        Long result = future.get();
        System.out.println(result);
        String another = texts.get();
        String that = text.get();
        System.out.println( another);
        System.out.println( that);
        cachedPool.shutdown();
    }

        public static void scheduledPool(){
            ScheduledExecutorService scheduledExecutorService = Executors.newScheduledThreadPool(5);

            ScheduledFuture scheduledFuture = scheduledExecutorService.schedule((Callable) Ex2::call, 5, TimeUnit.SECONDS);
            scheduledExecutorService.shutdown();
        }


    public static void main(String[] args) throws ExecutionException, InterruptedException {
        SingleThreadExec();
        FixedThreadPool();
        CachedPool();
        scheduledPool();
    }

    private static Object call() {
        System.out.println("Scheduled pool Executed!");
        return "Called!";
    }
}
