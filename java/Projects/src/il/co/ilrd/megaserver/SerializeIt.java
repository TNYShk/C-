package il.co.ilrd.megaserver;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.nio.ByteBuffer;

public interface SerializeIt {
    Object deserialize(ByteBuffer buffer) throws IOException, ClassNotFoundException;
    ByteBuffer serialize(Object serverMsg) throws IOException;

    //byte[] serialize(Object object) throws IOException;

}
