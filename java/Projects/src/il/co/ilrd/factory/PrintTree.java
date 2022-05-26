package il.co.ilrd.factory;

import java.io.File;
import java.util.*;


public class PrintTree {
    private final TreeFolder root;
     Factory<Boolean, Component, File> treeFactory = new Factory<>();
     static Map<String,Integer> dogMap = new HashMap<>(); /* to store all occurrences of 'dog'*/

    public PrintTree(String path) {
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
        private final List<PrintTree.Component> componentsList = new ArrayList<>();
        private final File folder;


        public TreeFolder(String path) {
            folder = new File(path);
            treeFactory.add((lambda) -> new TreeFolder(lambda.getPath()), true);
            treeFactory.add((lambda) -> new TreeFile(lambda.getPath()), false);

            for(File file: Objects.requireNonNull(folder.listFiles())){
                componentsList.add( treeFactory.create(file.isDirectory(), file));
               if(file.getName().contains(new StringBuffer("dog")))
                   dogMap.merge(file.getName(),1,Integer::sum);
            }
        }
        @Override
        public void print(int level) {

            System.out.println(dashMaker(level) + "_ " + folder.getName());

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
        private final File file;

        public TreeFile(String name) {
            file = new File(name);
        }
        @Override
        public void print(int level) {

            System.out.println("\t" + dashMaker(level) + "----" +getName());
        }
        @Override
        public String getName() {
            return file.getName();
        }
    }
    private StringBuilder dashMaker(int level){
        StringBuilder dash = new StringBuilder();

        while(--level>0){
            dash.append(" ");
        }
        dash.append("|");
        return dash;
    }
}
