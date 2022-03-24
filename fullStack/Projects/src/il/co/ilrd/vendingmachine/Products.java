package il.co.ilrd.vendingmachine;

public enum Products {
    EMPTY(0, " "),
    COLA(8, "coca-cola"),
    WATER(5.5, "Neviot"),
    COFFEE(7,"espresso"),
    CANDY(9.9, "kitkat"),
    BEER(20,"Goldstar");

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
