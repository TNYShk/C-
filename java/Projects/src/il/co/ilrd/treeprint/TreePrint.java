package il.co.ilrd.treeprint;

import java.util.ArrayList;

import java.util.List;
import java.io.File;

public class TreePrint {
    private TreeFolder root;

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
        private File folder;
        private File[] folders;
        public TreeFolder(String path) {

            folder = new File(path);
            folders = folder.listFiles();
            //componentsList.toArray(folders);
            for(File file: folders){
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
            System.out.println(bla.getName().toUpperCase());
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
