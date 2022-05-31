package il.co.ilrd.megaserver;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.nio.ByteBuffer;

public interface SerializeIt {
    Object deserialize(ByteBuffer buffer) throws IOException, ClassNotFoundException;
    ByteBuffer serialize(Object serverMsg) throws IOException;

     static byte[] serializeB(Object object) throws IOException {
        try (ByteArrayOutputStream bos = new ByteArrayOutputStream()) {
            try (ObjectOutputStream oos = new ObjectOutputStream(bos)){
                oos.writeObject(object);
                oos.flush();
                return bos.toByteArray();
            }
        }
    }


}
