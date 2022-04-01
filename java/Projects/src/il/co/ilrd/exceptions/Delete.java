package il.co.ilrd.exceptions;



public class Delete {

    public void func4() throws ArrayIndexOutOfBoundsException, NullPointerException{

        boolean []bb = new boolean[4];
        Boolean b = null;

        System.out.println("\nbb is "+bb[2] );
        try{
            bb[5] = false;
        } catch(ArrayIndexOutOfBoundsException e){
            System.out.println("OUT OF BOUNDS!");
            System.err.println(e);
        }
        try{
            System.out.println(b? true : false);
        } catch(NullPointerException e){
            System.out.println("NULL!");
            System.err.println(e);
        }

    }
}
