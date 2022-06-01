package il.co.ilrd.multiserverprotocol;

public enum PingPongKeys {
    PING{
        @Override
        public PingPongKeys reply() {return PONG;}
    },
    PONG{
        @Override
        public PingPongKeys reply() {return PING;}
    },
    ERROR_PINGPONG_KEYS{
        @Override
        public PingPongKeys reply() {return ERROR_PINGPONG_KEYS;}
    };


    public abstract PingPongKeys reply();
}
