
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

class Circle extends Shape{
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

class Rectangle extends Shape{
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

class Square extends Rectangle{
	
	public Square() {
		super();
	}
	public Square(double side) {
		super(side,side);
	}
	public Square(double side, String color, boolean fill) {
		super(side,side,color,fill);
		
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
		return "a Square w. area " + getArea() + " which is a subclass of "+ super.toString();
	}
}

