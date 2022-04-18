package il.co.ilrd.shapes;

public class Circle extends Shape{
    protected double radius;

    public Circle() {
        super();
        radius = 1.0;
    }
    public Circle(String color, boolean fill) {
        super(color,fill);
        radius = 1.0;
    }
    public Circle(double radius, String col, boolean fill) {
        super(col,fill);
        this.radius = radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }
    public double getRadius() {
        return radius;
    }

    public double getPerimeter() {
        return (2 * Math.PI * radius);
    }

    public double getArea() {
        return ( Math.PI * radius * radius);
    }

    @Override
    public String toString() {
        return "a circle w. radius " + radius + " which is a subclass of "+ super.toString();
    }
}