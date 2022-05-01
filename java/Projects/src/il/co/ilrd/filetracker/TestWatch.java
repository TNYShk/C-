package il.co.ilrd.filetracker;

import java.io.IOException;

public class TestWatch {

    public static void main(String[] args) throws IOException, InterruptedException {
        String filePath = "/Users/tanyashkolnik/Documents/Education/Infinity/shoshana.txt";
        String backFile = "/Users/tanyashkolnik/Documents/Education/Infinity/backup.txt";
        FileTracker test = new FileTracker(filePath, backFile);
        test.startMonitor();
        Thread.sleep(20000);
        test.endMonitor();
    }
}
/*
   WatchService watch = FileSystems.getDefault().newWatchService();
        Path path = Paths.get("/home/tanya/Downloads");

        WatchKey watchkey = path.register(watch, StandardWatchEventKinds.ENTRY_CREATE,
                StandardWatchEventKinds.ENTRY_DELETE, StandardWatchEventKinds.ENTRY_MODIFY);
        while ((watchkey = watch.take()) != null) {
            // inner loop to go over all the events that occurred (pollEvents return array of events that happened)
            for (WatchEvent<?> event : watchkey.pollEvents()) {
                // print the event kind (creation, modify, delete, etc..)
                System.out.println("Event that happened: " + event.kind());
                // print the file name that was affected.
                System.out.println("File affected: " + event.context());
                System.out.println();
            }
            // must reset the watchkey in order for it to be able to use another take().
            watchkey.reset();
        }

        // to test it use your own path in line 18, must be directory path, and
        // while the process is running make changes to files in the class and u will
        // see the prints in the terminal.
 */