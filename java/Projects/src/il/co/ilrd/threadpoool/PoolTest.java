package il.co.ilrd.threadpoool;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.testng.AssertJUnit.assertTrue;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

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
    void testSubmitShai() throws InterruptedException, ExecutionException {
        Callable<Integer> call1 = () -> 1;
        Callable<Integer> call2 = () -> 2;
        Callable<Integer> call3 = () -> 3;
        Runnable run1 = () -> System.out.println("im a runner 1");
        ThreadPool tp = new ThreadPool(3);
        Future<Integer> f1 = tp.submit(call1, ThreadPool.Priority.LOW);
        Future<Integer> f2 = tp.submit(call2, ThreadPool.Priority.HIGH);
        Future<Integer> f3 = tp.submit(call3); // should be MID priority
        Future<Void> r1 = tp.submit(run1, ThreadPool.Priority.HIGH);
        Thread.sleep(1000);
        assertTrue(f1.get().equals(1));
        assertTrue(f2.get().equals(2));
        assertTrue(f3.get().equals(3));
        assertTrue(r1.get() == null);
    }
}
