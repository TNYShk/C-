package il.co.ilrd.waitablepriorityqueue;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;
import java.util.Comparator;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;


public class TestimTest {

    @Test
    void CondVarBasicTest() throws InterruptedException {

        WaitablePriorityQCondVar<Number> Tanya = new WaitablePriorityQCondVar<>(10);
        Thread[] yyy = new Thread[100];

        for (int i = 0; i < 100; ++i) {

            int finalI = i;
            yyy[i] = new Thread(() -> {
                try{
                    Tanya.enqueue(finalI);
                    Tanya.dequeue();

                }catch(InterruptedException e){
                    System.err.println("I HATE THIS");
                }
            });
            yyy[i].start();
        }
        Thread.sleep(1000);
        System.out.println("where?! " + Tanya.size());
        Assertions.assertTrue(Tanya.isEmpty());
        //assertEquals(0,Tanya.size());
        //System.out.println("where?! " + Tanya.size());

    }

    @Test
    void anotherCVTest() throws InterruptedException {
        WaitablePriorityQCondVar<Number> Tanya = new WaitablePriorityQCondVar<>(Comparator.comparingInt(Number::intValue),1,20);

        Thread[] dQer = new Thread[50];
        Thread[] Qer = new Thread[50];

        for(int i = 0 ; i< 50; ++i){
            dQer[i] = new Thread(() -> {
                try{
                    Tanya.dequeue();

                }catch(InterruptedException e){
                    System.err.println("I HATE THIS");
                }
            });
            dQer[i].start();
            Assertions.assertTrue(Tanya.isEmpty());

        }
        for(int i = 0 ;i < 50; ++i){
            int finalI = i*i;
            Qer[i] = new Thread(() -> {
                try{
                    Tanya.enqueue(finalI);

                }catch(InterruptedException e){
                    System.err.println("I HATE THIS");
                }
            });
            Qer[i].start();
        }
        Thread.sleep(1000);
        assertTrue(Tanya.isEmpty());
       //System.out.println("size is:" + Tanya.size());
    }

    @Test
    void removeCVTest() throws InterruptedException {
        WaitablePriorityQCondVar<Number> Tanya = new WaitablePriorityQCondVar<>(1,100);
        assertTrue(Tanya.isEmpty());
        Thread[] reMovers = new Thread[100];

        for (int i = 0; i < 100; ++i) {
            int finalI = i;
            reMovers[i] = new Thread(() -> {
                try{
                    Tanya.enqueue(finalI);
                    Tanya.remove(finalI*finalI); /* should remove only 0,1*/

                }catch(InterruptedException e){
                    System.err.println(e + "\n I HATE THIS");
                }
            });
            reMovers[i].start();
            reMovers[i].join();
        }
       // System.out.println("size is:" + Tanya.size());
        assertEquals( 98, Tanya.size());
        assertTrue( Tanya.remove(26));
        assertEquals( 97, Tanya.size());
        assertFalse(Tanya.remove(26));
        assertFalse(Tanya.remove(0));
        assertFalse(Tanya.remove(1));

    }
    @Test
    void SemTest() throws InterruptedException {
        WaitablePriorityQueueSem<String> Stanya = new WaitablePriorityQueueSem<>(5);
        assertTrue(Stanya.isEmpty());
        Thread[] Qer = new Thread[11];
        String str = "z";
        StringBuffer s = new StringBuffer(str);
        for(int i =0; i<11; ++i){
            s.append("z");
            str = String.valueOf(s);
            String finalStr = str;
            Qer[i] = new Thread(() -> {
                try{
                    Stanya.enqueue(finalStr);

                } catch (InterruptedException e) {
                 e.printStackTrace();
                }
            });
            Qer[i].start();
        }
      Thread.sleep(1000);
        String sleepDeprived = Stanya.dequeue();
        System.out.println(sleepDeprived + "\t length: " + sleepDeprived.length());
       assertTrue(sleepDeprived.length() >= 2);
       // Stanya.enqueue(sleepDeprived);
      //assertFalse(Stanya.remove(sleepDeprived.substring(30)));
        assertTrue(Stanya.remove("zzzzzzzzzz"));
    }

    @Test
    void test1SemShai() throws InterruptedException {
        WaitablePriorityQCondVar<Integer> pq = new WaitablePriorityQCondVar<>(10);
        Thread t1 = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(2000);
                    int num = pq.dequeue();
                    assertEquals(num, 1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
        assertTrue(pq.isEmpty());
        assertEquals(pq.size(), 0);
        pq.enqueue(17);
        pq.enqueue(5);
        pq.enqueue(3);
        pq.enqueue(24);
        pq.enqueue(67);
        int num = pq.dequeue();
        assertEquals(num, 3);
        assertFalse(pq.isEmpty());
        assertEquals(pq.size(), 4);
        pq.enqueue(1);
        pq.enqueue(7);
        pq.enqueue(13);
        pq.enqueue(2);
        pq.enqueue(6);
        pq.enqueue(43);
        pq.enqueue(41);

        t1.start();
        pq.enqueue(15);
        assertEquals(pq.size(), 11);

        assertTrue(pq.remove(7));
        assertFalse(pq.remove(102));
        assertEquals(pq.size(), 10);

        t1.join();

        }

    @Test
    public void DortestSem(){
        WaitablePriorityQueueSem<Integer> q = new WaitablePriorityQueueSem<>(10);

        Runnable R1 = new Runnable() {

            @Override
            public void run() {
                for(int i = 0; i < 12; ++i) {
                    System.out.println("added " + i );
                    try {
                        q.enqueue(i);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }

            }

        };
        Runnable R2 = new Runnable() {

            @Override
            public void run() {
                for(int i = 0; i < 11; ++i) {
                    try {
                        System.out.println("dequeue :" + q.dequeue());
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        };
        Runnable R3 = () -> {
            try {
                System.out.println("removed :" + q.remove(1));
            } catch (InterruptedException e) {
               e.printStackTrace();
            }
            try {
                System.out.println("removed :" + q.remove(11));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        };

        Thread t1 = new Thread(R1);
        Thread t2 = new Thread(R2);
        Thread t3 = new Thread(R3);

        t1.start();
        t2.start();
        t3.start();

        try {
            t1.join();
        } catch (InterruptedException e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }
        try {
            t2.join();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        try {
            t3.join();
        }
        catch (InterruptedException e) {
            // TODO: handle exception
            e.printStackTrace();
        }

    }



}
