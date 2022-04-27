package il.co.ilrd.filetracker;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Collections;
import java.util.List;

public class FileCrudIMP implements CRUD<Long,String> {
    private Path file;

    public FileCrudIMP(String path){
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
