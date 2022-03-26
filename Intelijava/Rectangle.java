package Shapes;

public class Rectangle extends Shape{
    protected double width;
    protected double length;

    public Rectangle() {
        width = length =  1.0;
    }

    public Rectangle(double width, double length) {
        this.width = width;
        this.length = length;
    }
    public Rectangle(double width, double length, String color, boolean filled) {
        super(color,filled);
        this.width = width;
        this.length = length;
    }
    public void setWidth(double newWidth) {
        width = newWidth;
    }
    public void setLength(double len) {
        length = len;
    }
    public double getWidth() {
        return width;
    }
    public double getLength() {
        return length;
    }

    @Override
    double getPerimeter() {
        return ((2* width) + (2 * length));
    }

    @Override
    double getArea() {
        return ( width * length);
    }

    @Override
    public String toString() {
        return "a Rectangle w. width " + width + " and length " + length + " which is a subclass of "+ super.toString();
    }
}