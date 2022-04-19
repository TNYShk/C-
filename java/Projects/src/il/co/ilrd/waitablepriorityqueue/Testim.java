package il.co.ilrd.waitablepriorityqueue;

import org.junit.jupiter.api.Test;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;


public class Testim   {

    @Test
    void CVTest() throws InterruptedException {

        WaitablePriorityQCondVar<Number> Tanya = new WaitablePriorityQCondVar<>(15);
        Thread[] yyy = new Thread[100];

        for (int i = 0; i < 100; ++i) {

            int finalI = i;
            yyy[i] = new Thread(new Runnable() {
                @Override
                public void run() {
                    try{
                        Tanya.enqueue(finalI);
                        Tanya.dequeue();
                    }catch(InterruptedException e){
                        System.err.println("I HATE THIS");
                    }
                }
            });
            yyy[i].start();
        }
        assertEquals(15,Tanya.size());
        //System.out.println("where?! " + Tanya.size());

    }

    @Test
    void anotherCVTest(){
        WaitablePriorityQCondVar<Number> Tanya = new WaitablePriorityQCondVar<>(20);

        Thread[] deQer = new Thread[50];
        Thread[] Qer = new Thread[50];

        for(int i = 0 ; i< 50; ++i){
            int finalI = i;
            deQer[i] = new Thread(() -> {
                try{
                    Tanya.dequeue();

                }catch(InterruptedException e){
                    System.err.println("I HATE THIS");
                }
            });
            deQer[i].start();
            assertTrue(Tanya.isEmpty());

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
        assertTrue(Tanya.size()> 0);
        System.out.println("size is:" + Tanya.size());
    }

    @Test
    void removeCVTest() throws InterruptedException {
        WaitablePriorityQCondVar<Number> Tanya = new WaitablePriorityQCondVar<>(100);
        Thread[] reMovers = new Thread[100];

        for (int i = 0; i < 100; ++i) {

            int finalI = i;
            reMovers[i] = new Thread(new Runnable() {
                @Override
                public void run() {
                    try{
                        Tanya.enqueue(finalI);
                        Tanya.remove(finalI*finalI); /* should remove only 0,1*/

                    }catch(InterruptedException e){
                        System.err.println("I HATE THIS");
                    }
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

}
