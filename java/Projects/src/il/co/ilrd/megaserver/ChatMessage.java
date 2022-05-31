package il.co.ilrd.megaserver;

import java.io.Serializable;

public class ChatMessage implements Message<ChatKeys,String>, Serializable {
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
}
