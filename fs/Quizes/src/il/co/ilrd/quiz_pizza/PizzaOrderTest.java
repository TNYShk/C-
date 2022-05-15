package il.co.ilrd.quiz_pizza;

public class PizzaOrderTest {

    public static void main(String[] args){
        Pizza myPizza = new Margarita();
        myPizza = new FreshTomato(myPizza);

        System.out.println(myPizza.getDescription());
        System.out.print("costs: " + myPizza.getPrice());
    }



}
