package il.co.ilrd.megaserver;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.util.concurrent.TimeUnit;


public class TestServer {
    @Test
    public void dryRun() throws IOException, InterruptedException, ClassNotFoundException {
       /* MultiProtocolServer testS = new MultiProtocolServer();
        testS.addTCP(10523);
        //testS.addUDP(10521);

        testS.serverUp();
        TimeUnit.SECONDS.sleep(10);*/
        ClientTCPTest clientallll = new ClientTCPTest();
        clientallll.communicate();
       /* TimeUnit.SECONDS.sleep(20);
        testS.serverDown();*/

    }


}
