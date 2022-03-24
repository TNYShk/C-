package il.co.ilrd.vendingmachine;

public interface Screen {
    default void Print(String toPrint){
        System.out.println(toPrint);
    }
}
