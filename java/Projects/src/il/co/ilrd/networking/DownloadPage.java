package il.co.ilrd.networking;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.nio.file.Files;
import java.nio.file.Paths;

public class DownloadPage {

    public static void downloadFile(URL url, String outputFileName) throws IOException
    {
        try (InputStream in = url.openStream()) {
            Files.copy(in, Paths.get(outputFileName));
        }
    }
    public static void downloadFileChannel(URL url, String outputFileName) throws IOException
    {
        try (InputStream in = url.openStream();
             ReadableByteChannel rbc = Channels.newChannel(in);
             FileOutputStream fos = new FileOutputStream(outputFileName)) {
            fos.getChannel().transferFrom(rbc, 0, Long.MAX_VALUE);
        }
    }

    public static void main(String[] args) throws Exception {
        String outputFileName = "/Users/tanyashkolnik/Documents/Education/Infinity/download.html";
        try {
            URL url = new URL("https://jenkov.com/tutorials/java-networking/jarurlconnection.html");
            URL url1 = new URL("https://docs.oracle.com/javase/tutorial/networking/sockets/definition.html");
            downloadFile(url,outputFileName );
            downloadFileChannel(url1,outputFileName);
        }catch(MalformedURLException e){
            System.err.print(e);
        }
        /*Thread.sleep(5000l);
        Files.delete(Paths.get(outputFileName));*/
    }

}
