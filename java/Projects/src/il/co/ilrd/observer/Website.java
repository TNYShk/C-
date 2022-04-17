package il.co.ilrd.observer;

public class Website {
    private final Dispatcher<StringBuffer> dispatch = new Dispatcher<>();
    private final String name;

    public Website(String name) {
        this.name = name;
    }

    public void subscribe(Callback<StringBuffer> site){
        dispatch.register(site);
    }

    public void unsubscribe(Callback<StringBuffer> site){
        dispatch.unregister(site);
    }

    public Dispatcher<StringBuffer> getDispatcher() {
        return dispatch;
    }
    public String getName(){
        return name;
    }
}
