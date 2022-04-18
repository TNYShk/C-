package il.co.ilrd.observer;

import il.co.ilrd.hashMap.Pair;

import java.util.function.Consumer;

public class Subscriber {

    private Callback<StringBuffer> provider;

    public Subscriber(Consumer<StringBuffer> howNotify, Runnable howStopNotify){
        //Pair<Consumer,Runnable> communicationType = Pair.of(howNotify,howStopNotify);
        provider = new Callback<>(howNotify,howStopNotify);
    }


    public void subscribe(Website outlet){
        System.out.println("welcome to " + outlet.getName() + " ");
        outlet.subscribe(provider);

    }

    public void unsubscribe(Website outlet){
        System.out.println("you've unsubscribed from " + outlet.getName() );
        outlet.unsubscribe(provider);
    }


}
