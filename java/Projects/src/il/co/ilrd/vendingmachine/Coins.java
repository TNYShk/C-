package il.co.ilrd.vendingmachine;

public enum Coins {
    AGORA(0.10),
    HALFS(0.5),
    SHEKEL(1.0),
    SHNEKEL(5.0),
    FIVES(5.0),
    TENS(10);

    private double value;

    Coins(double value) {
        this.value = value;
    }



    public double getValue() {
        return value;
    }
}
