package il.co.ilrd.filetracker;

import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class TestWatch {

    public static void main(String[] args)  {

    }

    @Test
    void Test() throws IOException, InterruptedException {
        String filePath = "/Users/tanyashkolnik/Documents/Education/Infinity/shoshana.txt";
        String backFile = "/Users/tanyashkolnik/Documents/Education/Infinity/backup.txt";
        FileTracker test = new FileTracker(filePath, backFile);
        test.startMonitor();
        Thread.sleep(20000);
        test.endMonitor();
        Files.delete(Paths.get(backFile));
    }
}
