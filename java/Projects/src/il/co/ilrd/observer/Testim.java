package il.co.ilrd.observer;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.util.function.Consumer;

public class Testim {

    Consumer<StringBuffer> notifyByMail = (data) -> System.out.println(" by email: " + data);
    //GIANT ASS
    Runnable stopByMail = System.out::println;

    Consumer<StringBuffer> notifyFax = (data) -> System.out.println(" by Fax: " + data);
    //GIANT ASS
    Runnable stopByFax = () -> System.out.println("unsubscribed by Fax");

    Consumer<StringBuffer> notifyBySMS = (data) -> System.out.println("SMS: " + data);
    //GIANT ASS
    Runnable stopBySMS = () -> System.out.println("unsubscribed by SMS");

    @Test
    void ynetTest(){
        Website ynet = new Website("ynet");
        Subscriber Tanya = new Subscriber(notifyByMail, stopByMail);
        Subscriber Moshe = new Subscriber(notifyFax, stopByFax);
        Tanya.subscribe(ynet);
        Moshe.subscribe(ynet);
        StringBuffer msg = new StringBuffer();
        msg.append("bla bla bla lies");

        assertEquals(ynet.getDispatcher().getListSize(),2);
        ynet.getDispatcher().notifyAll(msg);
        Tanya.unsubscribe(ynet);
        assertEquals(ynet.getDispatcher().getListSize(),1);
        Tanya.subscribe(ynet);
        ynet.getDispatcher().stopNotification();
        assertEquals(ynet.getDispatcher().getListSize(),0);
        //System.out.println(ynet.getDispatcher().getListSize());
    }




}
