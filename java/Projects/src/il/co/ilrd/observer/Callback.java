package il.co.ilrd.observer;

import il.co.ilrd.hashMap.Pair;

import java.util.function.Consumer;

public class Callback<D> {
    private final Consumer<D> notification;
    private final Runnable stopNotification;
    private Dispatcher<D> dispatch;
    //public Pair<D,Runnable> subscriptionType;

    public Callback(Consumer<D> notify, Runnable stop) {
      notification = notify;
      stopNotification = stop;
      //subscriptionType = (Pair<D, Runnable>) Pair.of(notify,stop);
    }


    public void notify(D data) {

          notification.accept(data);
    }

    public void stopNotification() {
       stopNotification.run();
    }

    public void setDispatcher(Dispatcher<D> dispatcher){
        dispatch = dispatcher;
    }

    public void unsubscribe(){
        dispatch.unregister(this);
    }


}
