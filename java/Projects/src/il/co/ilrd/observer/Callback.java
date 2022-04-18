package il.co.ilrd.observer;
/*
    Observer Pattern WS
    by Tanya Shk
    April 18, 2022
    reviewed by Shoshana
 */


import java.util.function.Consumer;

public class Callback<D> {
    private final Consumer<D> notification;
    private final Runnable stopNotification;
    private Dispatcher<D> dispatch;


    public Callback(Consumer<D> notify, Runnable stop) {
      notification = notify;
      stopNotification = stop;
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
