package il.co.ilrd.filetracker;

import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import static org.junit.Assert.assertEquals;

public class TestWatch {

    public static void main(String[] args) {


    }

    @Test
    void Test() throws IOException, InterruptedException {
        String filePath = "/home/tanya/Documents/bla.txt";
        String backFile = "/home/tanya/Documents/backup.txt";
        FileTracker test = new FileTracker(filePath, backFile);
        test.startMonitor();
        Thread.sleep(60000);
        test.endMonitor();
        Files.delete(Paths.get(backFile));
    }

    @Test
    void anotherTest() throws IOException, InterruptedException {

        FileCrudIMP filing = new FileCrudIMP("/home/tanya/Documents/bla.txt");
        filing.create("adding data!");
        long checkLine = filing.create("give me more data!");
        assertEquals(checkLine,filing.numberOfLines());
        assertEquals(filing.read(checkLine),"give me more data!");
        String filePath = "/home/tanya/Documents/bla.txt";
        String backFile = "/home/tanya/Documents/bbackup.txt";
        FileTracker monitor = new FileTracker(filePath, backFile);
        File bb = new File(backFile);

        bb.createNewFile();


        monitor.startMonitor();


        filing.create("let the games begin!");

        filing.update(1L,"update is here");
        filing.delete(1L);
        //Thread.sleep(20000);

        //monitor.endMonitor();





    }


}
