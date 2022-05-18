package il.co.ilrd.megaserver;

public enum PingPongKeys {
    PING{
        @Override
        public PingPongKeys reply() {return PONG;}
    },
    PONG{
        @Override
        public PingPongKeys reply() {return PING;}
    },
    NOT_P_ERROR{
        @Override
        public PingPongKeys reply() {return NOT_P_ERROR;}
    };


    public abstract PingPongKeys reply();
}
