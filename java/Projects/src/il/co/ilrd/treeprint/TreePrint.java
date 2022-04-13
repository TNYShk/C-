package il.co.ilrd.treeprint;
/*
    TreePrint - print folders&files in given path
    by Tanya Shk
    April 13, 2022
    reviewed by Daniela
 */

import java.util.ArrayList;
import java.util.List;
import java.io.File;
import java.util.Objects;

public class TreePrint {
    private final TreeFolder root;

    public TreePrint(String path) {
        root = new TreeFolder(path);
    }

    public void tree() {
        root.print(0);
    }

    private interface Component {
        void print(int level);
        String getName();
    }

    private class TreeFolder implements Component {
        private List<Component> componentsList = new ArrayList<>();
        private final File folder;

        public TreeFolder(String path) {

            folder = new File(path);

            for(File file: Objects.requireNonNull(folder.listFiles())){
                if(file.isDirectory()){
                    componentsList.add(new TreeFolder(file.getPath()));
                }else if(file.isFile()){
                    componentsList.add(new TreeFile(file.getPath()));
                }
            }
        }

        @Override
        public void print(int level) {
            TreePrint.TreeFile bla = new TreeFile(folder.getPath());
            System.out.println(bla.getName() + "\n |_");
            for(Component comp: componentsList ){
                comp.print(level+1);
            }
        }

        @Override
        public String getName() {
           return folder.getName();

        }
    }

    private class TreeFile implements Component {
        private File file;

        public TreeFile(String name) {
            file = new File(name);
        }
        @Override
        public void print(int level) {
            StringBuilder dash = new StringBuilder(" | ");
            while(level>0){
                --level;
                dash.append("-");
            }
           System.out.println("\t" + dash + " " +getName());
        }
        @Override
        public String getName() {
           return file.getName();
        }
    }
}
