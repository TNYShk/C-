package il.co.ilrd.threadpoool;
import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.testng.AssertJUnit.assertTrue;

import java.util.concurrent.*;

import org.junit.jupiter.api.Test;

public class PoolTest {

    @Test
    public void testSubmit1Arg() {

        ThreadPool deadpool = new ThreadPool(3);

        Callable<Integer> task = () -> (1+2);

        try {
            Future<Integer> result = deadpool.submit(task);
            System.out.println(result.get());
            assertEquals(3, result.get());
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
    }
    @Test
    public void Submit2Arg(){
        Runnable run1 = () -> System.out.println("tanya hey");
        ThreadPool pool = new ThreadPool(2);

        try {
            pool.submit(run1, ThreadPool.Priority.HIGH);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Test
    void testSubmitShai() throws InterruptedException, ExecutionException, TimeoutException {
        Callable<Integer> call1 = () -> 1;
        Callable<Integer> call2 = () -> 2;
        Callable<Integer> call3 = () -> 3;
        Callable<Double> complexCalc = () -> (1.0 -(1.0/3)+ (1/5.0) - (1.0/7) + (1/9.0));
        Runnable run1 = () -> System.out.println("im a runner 1");

        ThreadPool tp = new ThreadPool(3);
        Double answer  = 11.0;
        Runnable run = () -> System.out.println(" the ans is " + answer);
        Future<Double> c1 = tp.submit(complexCalc,ThreadPool.Priority.MED);
        Future<Integer> f1 = tp.submit(call1, ThreadPool.Priority.LOW);
        Future<Integer> f2 = tp.submit(call2, ThreadPool.Priority.HIGH);
        Future<Integer> f3 = tp.submit(call3); // should be MID priority
        Future<Void> r2 = tp.submit(run1, ThreadPool.Priority.HIGH);
        Future<Double> r1 = tp.submit(run, ThreadPool.Priority.HIGH, answer);
        Future<Long> future = tp.submit(() -> {
            long sum = 0;
            int block = 5000;
            while(--block > 0);

            for(long i = 0; i<= 10000000l; ++i){
                sum += i;
            }
            return sum;
        },ThreadPool.Priority.HIGH);
        System.out.println((future.get()));
        assertTrue(f1.get().equals(1));
        assertTrue(f2.get().equals(2));
        assertTrue(f3.get().equals(3));
        System.out.println((c1.get(10l, TimeUnit.SECONDS)));
        assertTrue(c1.get(10l, TimeUnit.SECONDS).equals(0.8349206349206351));
        assertTrue(r2.get() == null);
        assertTrue(r1.get() == 11.0);
    }

    @Test
    void priorityTest() throws InterruptedException {
        ThreadPool tp = new ThreadPool(1);
        tp.submit(() -> {
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {}

        }, ThreadPool.Priority.MED);

        for (int i = 0; i < 3; ++i) {
            tp.submit(() -> System.out.print("LOW  "), ThreadPool.Priority.LOW);
            tp.submit(() -> System.out.print("MED  "), ThreadPool.Priority.MED);
            tp.submit(() -> System.out.print("anotherMED  "), ThreadPool.Priority.MED);
            tp.submit(() -> System.out.print("HIGH  "), ThreadPool.Priority.HIGH);
            tp.submit(() -> System.out.print("anotherHIGH  "), ThreadPool.Priority.HIGH);
        }

        Thread.sleep(5000);
    }

}
