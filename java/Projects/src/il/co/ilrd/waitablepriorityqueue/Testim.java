package il.co.ilrd.waitablepriorityqueue;

import jdk.internal.platform.cgroupv1.SubSystem;
import org.junit.jupiter.api.Test;

import java.util.Collections;
import java.util.Comparator;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;


public class Testim   {

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
        assertTrue(Tanya.isEmpty());
        //assertEquals(0,Tanya.size());
        //System.out.println("where?! " + Tanya.size());

    }

    @Test
    void anotherCVTest(){
        WaitablePriorityQCondVar<Number> Tanya = new WaitablePriorityQCondVar<>(Comparator.comparingInt(Number::intValue),1,20);

        Thread[] deQer = new Thread[50];
        Thread[] Qer = new Thread[50];

        for(int i = 0 ; i< 50; ++i){
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
}
