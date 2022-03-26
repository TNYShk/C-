package Shapes;
abstract class Shape {

    protected String color;
    protected boolean filled;

    public Shape() {
        color = new String("green");
        filled = true;
    }

    public Shape(String col, boolean fill) {
        this.color = col;
        this.filled = fill;
    }
    public void setColor(String color) {
        this.color = color;
    }
    public void setFiller(boolean filler) {
        this.filled = filler;
    }

    public String getColor() {
        return this.color;
    }

    public String toString() {
        return "a " + color + " colored shape " ;
    }

    public boolean isFilled() {
        if(filled) {
            System.out.print(" shape fillled! ");
        }else {
            System.out.print(" shape empty! ");
        }
        return filled;

    }
    abstract double getArea();
    abstract double getPerimeter();

}

