package il.co.ilrd.treeprint;



public class PathTest {
    public static void main(String[] args){
        TreePrint shoshana = new TreePrint("/Users/tanyashkolnik/Downloads");
        shoshana.tree();

        try{
            TreePrint Tanya = new TreePrint(null);
            Tanya.tree();
        }catch (IllegalArgumentException e){
            System.err.println(e);
        }


    }

}
