package il.co.ilrd.observer;


import java.util.function.Consumer;

public class Subscriber {
    private final Callback<StringBuffer> provider;

    public Subscriber(Consumer<StringBuffer> howNotify, Runnable howStopNotify){

        provider = new Callback<>(howNotify,howStopNotify);
    }

    public void subscribe(Website outlet){
        System.out.println("subscriber! welcome to " + outlet.getName() + " ");
        outlet.subscribe(provider);
    }

    public void unsubscribe(Website outlet){
        System.out.println("you've unsubscribed from " + outlet.getName() );
        outlet.unsubscribe(provider);
        provider.unsubscribe();
        provider.stopNotification();
    }

}
