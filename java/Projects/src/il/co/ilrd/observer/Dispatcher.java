package il.co.ilrd.observer;
/*
    Observer Pattern WS
    by Tanya Shk
    April 18, 2022
    reviewed by Shoshana
 */


import java.util.LinkedList;
import java.util.List;


public class Dispatcher<D> {
    private List<Callback<D>> callbacklist = new LinkedList<>();

    public void register(Callback<D> callback) {
        callbacklist.add(callback);
        callback.setDispatcher(this);
    }

    public void unregister(Callback<D> callback) {
        callbacklist.remove(callback);
    }

    public void notifyAll(D data) {
        for (Callback<D> callback : callbacklist) {
            callback.notify(data);
        }
    }

    public void stopNotification() {
        for (Callback<D> callback : callbacklist) {
            callback.stopNotification();
        }
        callbacklist.clear();
    }
    /* for testing purposes, not part of API*/
    public int getListSize(){
        return callbacklist.size();
    }
}
