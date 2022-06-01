package il.co.ilrd.multiserverprotocol;

public class ChatMessage implements Message<ChatKeys,String> {
    private static final long serialVersionUID = 1L;
    private ChatKeys chatKey;
    private String text;

    public ChatMessage(ChatKeys chatKey, String msg ){
        this.chatKey = chatKey;
        this.text = msg;
    }

    @Override
    public ChatKeys getKey() {
       return chatKey;
    }

    @Override
    public String getData() {
       return text;
    }

    @Override
    public String toString(){return "ChatMessage";}
}
