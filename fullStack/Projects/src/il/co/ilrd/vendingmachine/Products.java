package il.co.ilrd.vendingmachine;

public enum Products {
    EMPTY(0, " "),
    COLA(10, "coca-cola"),
    WATER(15, "neviot"),
    COFFEE(6.7,"espresso"),
    CANDY(5.5, "kitkat"),
    BEER(20,"nesher");

    private double price;
    private String name;

    Products(double price, String name) {
        this.name = name;
        this.price = price;
    }

    public double getPrice() {
        return this.price;
    }

    public String getName(){
        return name;
    }
}
