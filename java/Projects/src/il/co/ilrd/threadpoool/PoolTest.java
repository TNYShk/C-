package il.co.ilrd.threadpoool;
import static org.junit.jupiter.api.Assertions.assertEquals;

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
}
