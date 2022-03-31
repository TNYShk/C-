package il.co.ilrd.exceptions;



public class Delete {

    public void func4() throws ArrayIndexOutOfBoundsException, NullPointerException{

        boolean bb[] = new boolean[4];


        bb[2] = false;
        System.out.println("bb is "+bb[2] );
        bb[5] = false;

    }
}
