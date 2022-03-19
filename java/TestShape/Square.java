package Test;

public class Square extends Rectangle {

    public Square() {
        super();
    }

    public Square(double side) {
        super(side, side);
    }

    public Square(double side, String color, boolean fill) {
        super(side, side, color, fill);

    }

    public double getSide() {
        return getWidth();
    }

    @Override
    public void setWidth(double side) {
        width = side;
    }

    @Override
    public void setLength(double side) {
        length = side;
    }

    @Override
    public String toString() {
        return "a Square w. area " + getArea() + " which is a subclass of " + super.toString();
    }
}