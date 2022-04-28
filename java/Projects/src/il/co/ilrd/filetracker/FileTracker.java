package il.co.ilrd.filetracker;

import il.co.ilrd.observer.Callback;
import il.co.ilrd.observer.Dispatcher;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.*;
import java.util.List;

public class FileTracker {
    private String path;
    private String backup;
    private FolderMonitor folderM;

    public void startMonitor() throws InterruptedException {
        folderM.run();
        //create inner thread since watcher is blocking
    }

    public void endMonitor() {
    }

    public FileTracker(String path, String backup) throws IOException {
       this.path = path;
       this.backup = backup;
       Path realPath = Paths.get(path);
        Path backupPath = Paths.get(backup);
       folderM = new FolderMonitor(realPath);
        FileMonitor fileM = new FileMonitor<>(realPath,backupPath);
        fileM.register(folderM);
        Files.copy(realPath,backupPath);
        }

        //create file Monitor
        //register fileMonitor to folderMonitor
        //create the backup file. duplicate of the initial file

    private static class FolderMonitor  {
       //watches folder and updates its subjects about the change n folder. subjects are files.
       private final WatchService watcher;
        private final Dispatcher<String> dispatch;
        public FolderMonitor(Path folder) throws IOException {
            dispatch = new Dispatcher<>();
            watcher =  FileSystems.getDefault().newWatchService();
          folder.register(watcher, StandardWatchEventKinds.ENTRY_CREATE,
                    StandardWatchEventKinds.ENTRY_DELETE, StandardWatchEventKinds.ENTRY_MODIFY);

        }
        public void run() throws InterruptedException {
            WatchKey watchkey;
            while ((watchkey = watcher.take()) != null) {

                for (WatchEvent<?> event : watchkey.pollEvents()) {
                        if(event.kind().name().equals(StandardWatchEventKinds.ENTRY_MODIFY))
                            dispatch.notifyAll();
                    System.out.println("Event that happened: " + event.kind());

                    System.out.println("File affected: " + event.context());
                    System.out.println();
                }
                // must reset the watchkey in order for it to be able to use another take().
                watchkey.reset();
            }
        }

        public void register(Callback<String> call){
            dispatch.register(call);

        }
    }
//Analyze changes in file. he is the observer. if the relevant to file, updates the backup file
    private class FileMonitor<ID,D>{
        private Callback<String> callback;
        private fileCrud<ID,D> crudFile;

        public FileMonitor(Path watchFile, Path backupFile){}

        public void register(FolderMonitor folderM){
            folderM.register(callback);
        }


    private class fileCrud<ID,D> implements CRUD<Long,String> {
          private Path file;

        public fileCrud(String path){
            file = Paths.get(path);
        }
        @Override
        public Long create(String data) throws IOException {
                Long line;
                FileWriter writing = new FileWriter(file.toFile(),true);

                try (BufferedWriter writer = new BufferedWriter(writing)) {
                    writer.write(data);
                    writer.newLine();
                }

                return Files.lines(file).count();
        }
        public long numberOfLines() throws IOException {
            return Files.lines(file).count();
        }

        @Override
        public String read(Long line) throws IOException {
            return  Files.readAllLines(file).get(line.intValue());
        }

        @Override
        public void update(Long line, String data) throws IOException {
            List<String> lines = Files.readAllLines(file);
            lines.set(line.intValue(), data);
            Files.write(file, lines);
        }

        @Override
        public void delete(Long line) throws IOException {
            List<String> lines = Files.readAllLines(file);
            lines.remove(line.intValue());
            Files.write(file, lines);
        }
    }
    }
}

