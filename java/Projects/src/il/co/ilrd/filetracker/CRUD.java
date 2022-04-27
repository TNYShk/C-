package il.co.ilrd.filetracker;

import java.io.IOException;

public interface CRUD<ID, D> {
    public ID create(D data) throws IOException;

    public D read(ID id) throws IOException;

    public void update(ID id, D data) throws IOException;

    public void delete(ID id) throws IOException;
}
