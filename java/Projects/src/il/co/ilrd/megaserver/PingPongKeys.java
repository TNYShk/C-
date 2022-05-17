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
    NOTP_ERROR{
        @Override
        public PingPongKeys reply() {return NOTP_ERROR;}
    };


    public abstract PingPongKeys reply();
}
