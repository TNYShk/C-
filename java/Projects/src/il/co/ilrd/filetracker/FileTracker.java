package il.co.ilrd.filetracker;

import il.co.ilrd.observer.Callback;
import il.co.ilrd.observer.Dispatcher;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.WatchService;
import java.util.List;

public class FileTracker {
    private String path;
    private String backup;
    private folderMonitor folderM;

    public void startMonitor() {
        folderM.run();
        //create inner thread since watcher is blocking
    }

    public void endMonitor() {
    }

    public FileTracker(String path, String backup) {
       this.path = path;
       this.backup = backup;
       //create folderMonitor
        //create file Monitor
        //register fileMonitor to folderMonitor
        //create the backup file. duplicate of the initial file
    }

    private class folderMonitor< D>  {
       //watches folder and updates its subjects about the change n folder. subjects are files.
       private WatchService watcher;
        private Dispatcher<D> dispatch;
        public folderMonitor(Path folder){


        }
        public void run(){}

        public void register(Callback<D> call){
            dispatch.register(call);

        }
    }
//Analyze changes in file. he is the observer. if the relevant to file, updates the backup file
    private class fileMonitor<ID,D>{
        private Callback<D> callback;
        //private FileCrud<ID,D> crudFile;

        public fileMonitor(Path watchFile, Path backupFile){}

        public void register(folderMonitor<D> folderM){
            folderM.register(callback);
        }


    private class fileCrud<ID,D> implements CRUD<Long,String> {
          private Path file;

        public fileCrud(String path){
            file = Paths.get(path);
        }
        @Override
        public Long create(String data) throws IOException {
                Long line = null;
                FileWriter writing = new FileWriter(file.toFile(),true);

                try (BufferedWriter writer = new BufferedWriter(writing)) {
                    writer.write(data);
                    writer.newLine();
                }

                line = Files.lines(file).count();

                return line;
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

