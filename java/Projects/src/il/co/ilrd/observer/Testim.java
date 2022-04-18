package il.co.ilrd.observer;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.function.Consumer;

public class Testim {

    Consumer<StringBuffer> notifyByMail = (data) -> System.out.println("by email: " + data);
    //GIANT ASS
    Runnable stopByMail = () -> System.out.println("unsubscribed from email notifications");

    Consumer<StringBuffer> notifyFax = (data) -> System.out.println("by Fax: " + data);
    //GIANT Runnable ass
    Runnable stopByFax = System.out::println; /*() -> System.out.println("unsubscribed by Fax");*/

    Consumer<StringBuffer> notifyBySMS = (data) -> System.out.println("by SMS: " + data);
    //GIANT Runnable ass
    Runnable stopBySMS = System.out::println; /*() -> System.out.println("unsubscribed by SMS");*/

    @Test
    void ynetTest(){
        Website ynot = new Website("ynet");
        Subscriber Tanya = new Subscriber(notifyByMail, stopByMail);
        Subscriber Poly = new Subscriber(notifyFax, stopByFax);
        Subscriber Shoshi = new Subscriber(notifyBySMS, stopBySMS);
        Subscriber Shayke = new Subscriber(notifyFax, stopByFax);

        Subscriber[] fs1145 = {Tanya,Poly,Shoshi, Shayke};
       for(int i = 0; i< fs1145.length ; ++i){
           fs1145[i].subscribe(ynot);
       }

        assertEquals(ynot.getDispatcher().getListSize(),4);
        StringBuffer msg = new StringBuffer();
        msg.append("bla bla bla lie");

        //ynot.getDispatcher().notifyAll(msg);
        ynot.notifyAll(msg);

        msg = new StringBuffer("חם מוות לא לצאת מהבית");
        ynot.getDispatcher().notifyAll(msg);

        ynot.notifyAll(new StringBuffer("more bla bla bla!"));
        Tanya.unsubscribe(ynot);
        assertEquals(ynot.getSize(),3);
        Tanya.subscribe(ynot);

        ynot.stopNotifications();
        assertEquals(ynot.getSize(),0);
        Tanya.subscribe(ynot);

        assertEquals(ynot.getSize(),1);
    }

    @Test
    void multipleSitesTest(){
        Website wawwa = new Website("walla");
        Subscriber Tanya = new Subscriber(notifyByMail, stopByMail);
        Subscriber Offer = new Subscriber(notifyFax, stopByFax);
        Subscriber Shoshi = new Subscriber(notifyBySMS, stopBySMS);
        Subscriber Shayke = new Subscriber(notifyFax, stopByFax);

        Website Shopping = new Website("ערוץ קניות");

        Subscriber[] fs1145 = {Tanya,Offer,Shoshi, Shayke};
        for(int i = 0; i< fs1145.length ; ++i){
            fs1145[i].subscribe(wawwa);
            fs1145[i].subscribe(Shopping);
        }

        assertEquals(wawwa.getDispatcher().getListSize(),4);
        assertEquals(Shopping.getDispatcher().getListSize(),4);
        StringBuffer junk = new StringBuffer("get this awesome couch for just 666$");
        StringBuffer walla = new StringBuffer("Scoop: Ben Caspit hates BB");

        wawwa.getDispatcher().notifyAll(walla);
        Shopping.notifyAll(junk);
        Tanya.unsubscribe(wawwa);
        Shoshi.unsubscribe(Shopping);
        Shopping.notifyAll(new StringBuffer("SALE! this awesome couch is now just 660$"));
        assertEquals(wawwa.getSize(),3);
        assertEquals(wawwa.getSize(),3);
        wawwa.stopNotifications();
        assertEquals(wawwa.getSize(),0);
    }




}
