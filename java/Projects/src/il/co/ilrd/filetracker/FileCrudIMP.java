package il.co.ilrd.filetracker;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

public class FileCrudIMP implements CRUD<Long,String> {
    private final Path backUPfile;

    public FileCrudIMP(String path){
        backUPfile = Paths.get(path);
    }
    @Override
    public Long create(String data) throws IOException {

        FileWriter writing = new FileWriter(backUPfile.toFile(),true);

        try (BufferedWriter writer = new BufferedWriter(writing)) {
            writer.write(data);
            writer.newLine();
        }

        return Files.lines(backUPfile).count();
    }

    public long numberOfLines() throws IOException {
            return Files.lines(backUPfile).count();
    }

    @Override
    public String read(Long line) throws IOException {
        return  Files.readAllLines(backUPfile).get(line.intValue() -1);
    }

    @Override
    public void update(Long line, String data) throws IOException {
        List<String> lines = Files.readAllLines(backUPfile);
        lines.set(line.intValue(), data);
        Files.write(backUPfile, lines);
    }

    @Override
    public void delete(Long line) throws IOException {
        List<String> lines = Files.readAllLines(backUPfile);
        lines.remove(line.intValue());
        Files.write(backUPfile, lines);
    }
}

