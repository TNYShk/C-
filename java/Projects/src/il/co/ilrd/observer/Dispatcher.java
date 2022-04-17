package il.co.ilrd.observer;

import java.util.List;
import java.util.ArrayList;

public class Dispatcher<D> {
    private List<Callback<D>> callbacklist = new ArrayList<>();

    public void register(Callback<D> callback) {
        callbacklist.add(callback);
        callback.setDispatcher(this);
    }

    public void unregister(Callback<?> callback) {
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
    public int getListSize(){
        return callbacklist.size();
    }
}
