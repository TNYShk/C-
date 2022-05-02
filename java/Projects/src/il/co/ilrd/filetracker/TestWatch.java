package il.co.ilrd.filetracker;

import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import static org.junit.Assert.assertEquals;

public class TestWatch {

    public static void main(String[] args)  {

    }

    @Test
    void Test() throws IOException, InterruptedException {
        String filePath = "/Users/tanyashkolnik/Documents/Education/Infinity/shoshana.txt";
        String backFile = "/Users/tanyashkolnik/Documents/Education/Infinity/backup.txt";
        FileTracker test = new FileTracker(filePath, backFile);
        test.startMonitor();
        Thread.sleep(30000);
        test.endMonitor();
        Files.delete(Paths.get(backFile));
    }

    @Test
    void anotherTest() throws IOException, InterruptedException {

        FileCrudIMP filing = new FileCrudIMP("/Users/tanyashkolnik/Documents/Education/Infinity/shoshana.txt");
        filing.create("adding data!");
        long checkLine = filing.create("give me more data!");
        assertEquals(checkLine,filing.numberOfLines());
        assertEquals(filing.read(checkLine),"give me more data!");
        String filePath = "/Users/tanyashkolnik/Documents/Education/Infinity/shoshana.txt";
        String backFile = "/Users/tanyashkolnik/Documents/Education/Infinity/backup.txt";
        FileTracker monitor = new FileTracker(filePath, backFile);
        monitor.startMonitor();


        filing.create("let the games begin!");
        filing.delete(1L);
        //Thread.sleep(30000);
        File bb = new File(backFile);
        File origin = new File(filePath);
        bb.createNewFile();
        origin.createNewFile();
        Thread.sleep(30000);
        //assertEquals(bb.compareTo(origin),0);

        monitor.endMonitor();





    }


}
