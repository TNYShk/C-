package il.co.ilrd.generics;


import java.util.*;

//No!
@SuppressWarnings("unchecked")
public class ItemTwentySeven<T> {
    T elements;
    int size;
    private final T[] choiceArray;
    private final List<T> myArr;

    //this is not ok, don't do it on a constructor!
    @SuppressWarnings("unchecked")
    public ItemTwentySeven(Collection<T> elements) {

        this.elements = (T) elements;
        this.size = 20;
        myArr = new ArrayList<>(elements);

        choiceArray = (T[]) elements.toArray();
    }

   public <T> T[] toArray(T[] t) {
        if (t.length < size) {
            //this cast is ok since the array created is of the same type as the one passed (T[]
            @SuppressWarnings("unchecked") T[] result =
             (T[]) Arrays.copyOf(choiceArray, size, t.getClass());
            return result;
        }
        System.arraycopy(choiceArray, 0, t, 0, size);

        if (t.length > size) {
            t[size] = null;
        }
        return t;
    }



    @Override
    public boolean equals(Object other) {
        if ((other instanceof ItemTwentySeven)) {
            ItemTwentySeven<T> otherPair = (ItemTwentySeven<T>) other;

            return ((this.elements.equals(otherPair.elements)) && (this.myArr.equals(otherPair.myArr)));
        }
        return false;
    }

    @Override
    public String toString(){
        return (this.elements.toString() );
    }
    @Override
    public int hashCode(){
        return this.elements.hashCode();
    }




}
