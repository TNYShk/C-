package il.co.ilrd.quiz_pizza;

public abstract class PizzaDecorator implements Pizza {


    @Override
    public String getDescription(){
        return  "with: ";
    }

    @Override
    public int getPrice() {
        return 0;
    }
}
