package il.co.ilrd.filetracker;

import il.co.ilrd.observer.Callback;
import il.co.ilrd.observer.Dispatcher;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.*;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.function.Consumer;

public class FileTracker {
  /*  private String path;
    private String backup;*/
    private FolderMonitor folderM;
    private AtomicBoolean starter = new AtomicBoolean();
    public void startMonitor(){
        Thread runProtection = new Thread(new Runnable() {
            @Override
            public void run() {
                starter.set(true);
                try {
                    folderM.run();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        });
        runProtection.start();

    }

    public void endMonitor() throws IOException {
        starter.set(false);
        folderM.watcher.close();
    }

    public FileTracker(String path, String backup) throws IOException {
       /*this.path = path;
       this.backup = backup;*/
        Path realPath = Paths.get(path);
        Path backupPath = Paths.get(backup);
        folderM = new FolderMonitor(realPath);
        FileMonitor fileM = new FileMonitor(realPath,backupPath);
        fileM.register(folderM);
        Files.copy(realPath,backupPath);
        }

        //create file Monitor
        //register fileMonitor to folderMonitor
        //create the backup file. duplicate of the initial file

    private class FolderMonitor  {
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
            while ((watchkey = watcher.take()) != null && (starter.get())) {

                for (WatchEvent<?> event : watchkey.pollEvents()) {
                        if(event.kind().name().equals(StandardWatchEventKinds.ENTRY_MODIFY))
                            dispatch.notifyAll((String) event.context());
                    /*System.out.println("Event that happened: " + event.kind());

                    System.out.println("File affected: " + event.context());
                    System.out.println();*/
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
    private class FileMonitor{
        private Callback<String> callback;
        private fileCrud crudFile;
        Path origin;

        public FileMonitor(Path watchFile, Path backupFile){
            Consumer<String> checkFile = (context) -> {
                try {
                    analyzeFile(context);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            };
            Runnable stopMonitor = () -> starter.set(false);
            origin = watchFile;
            crudFile = new fileCrud(backupFile);
            callback = new Callback<>(checkFile, stopMonitor);

        }

        public void analyzeFile(String context) throws IOException {
            if (context.equals(origin.getFileName().toString())){
                filesCompareByLine(origin, crudFile.file);
            }

        }
    public  void filesCompareByLine(Path watchFile, Path backupFile) throws IOException {
        List<String> originF = Files.readAllLines(watchFile);
        List<String> backUpp = Files.readAllLines(backupFile);
        int where = originF.size() - backUpp.size();

        if (where > 0) {
            crudFile.create(originF.get(originF.size() - 1));
        } else {
            int lineNum = 0;
            for (lineNum = 0; lineNum < backUpp.size() && (originF.get(lineNum).equals(backUpp.get(lineNum))); ++lineNum) {
            }
            if (where < 0) {
                crudFile.delete((long) lineNum);
            } else {
                crudFile.update((long) lineNum, originF.get(lineNum));
            }
        }
    }

        public void register(FolderMonitor folderM){
            folderM.register(callback);
        }


    private class fileCrud implements CRUD<Long,String> {
          private Path file;

        public fileCrud(Path path){
            file = path;
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

