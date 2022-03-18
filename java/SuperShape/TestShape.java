
public class TestShape {

public static void main(String[] args) {
	Shape s1 = new Circle(5.5, "RED", false);
    System.out.println(s1);
    System.out.println(s1.getArea());
    System.out.println(s1.getPerimeter());
    System.out.println(s1.getColor());
    System.out.println(s1.isFilled());
    System.out.println(((Circle)s1).getRadius()); // missing brackets and casting to cirle
    
    Circle c1 = (Circle)s1;
    System.out.println(c1);
    System.out.println(c1.getArea());
    System.out.println(c1.getPerimeter());
    System.out.println(c1.getColor());
    System.out.println(c1.isFilled());
    System.out.println(c1.getRadius()); // missing brackets
    
		/* Shape s2 = new Shape(); */ // abstract class, cant instantiate it
    
    Shape s3 = new Rectangle(1.0, 2.0, "RED", false);
    System.out.println(s3);
    System.out.println(s3.getArea());
    System.out.println(s3.getPerimeter());
    System.out.println(s3.getColor());
    System.out.println(((Rectangle)s3).getLength()); //method() was missing, also s3 is shape and no method length there
    
    Rectangle r1 = (Rectangle)s3;
    System.out.println(r1);
    System.out.println(r1.getArea());
    System.out.println(r1.getPerimeter());
    System.out.println(r1.getColor());
    System.out.println(r1.getLength()); //method() missing brackets
    
    Shape s4 = new Square(6.6);
    System.out.println(s4);
    System.out.println(s4.getArea());
    System.out.println(s4.getColor());
    System.out.println(((Square)s4).getSide()); //method() missing brackets and casting
    
    Rectangle r2 = (Rectangle)s4;
    System.out.println(r2);
    System.out.println(r2.getArea());
    System.out.println(r2.getColor());
    System.out.println(((Square)r2).getSide()); //down cSTING TO SQUARE, AND BRACKETS
    System.out.println(r2.getLength());
    
    Square sq1 = (Square)r2;
    System.out.println(sq1);
    System.out.println(sq1.getArea());
    System.out.println(sq1.getColor());
    System.out.println(sq1.getSide()); // missing brackets
    System.out.println(sq1.getLength()); // missing brackets
    System.out.println("\n\t Thanks, now Tanya's Tests: \n");
    methodTest();
	}

 static void methodTest(){
	Shape test = new Circle();
	Rectangle rex = new Rectangle(4.2,2.0,"BLUE", false); 
	Rectangle sq = new Square(6, "black", true);
	System.out.println(test);

	System.out.println("rectangle perimeter: " + rex.getPerimeter());
	System.out.println("rectangle area: " + rex.getArea());
	System.out.println(rex);
	((Circle)test).setRadius(2.1);
	test.setColor("red");
	((Circle)test).setColor("not red");
	System.out.println("circle area: " + test.getArea());
	System.out.println(test);
	System.out.println(sq);
	}
}
