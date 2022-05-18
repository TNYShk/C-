package il.co.ilrd.megaserver;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.util.concurrent.TimeUnit;


public class TestServer {
    @Test
    public void dryRun() throws IOException, InterruptedException, ClassNotFoundException {

        ClientTCPTest clientallll = new ClientTCPTest();
        clientallll.communicate();
       /* TimeUnit.SECONDS.sleep(20);
        testS.serverDown();*/

    }


}
