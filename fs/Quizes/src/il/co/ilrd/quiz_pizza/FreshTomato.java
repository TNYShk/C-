package il.co.ilrd.quiz_pizza;

public class FreshTomato extends PizzaDecorator{
    private Pizza pizza;

    public FreshTomato(Pizza pizza) {

        this.pizza = pizza;
    }

    @Override
    public String getDescription() {
        return  pizza.getDescription() +"fresh tomato " /*+ getPrice()*/;
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() +1;
    }
}
