package il.co.ilrd.quiz2;

public class Point {
    private int x = 0, y;

    public Point(int x, int y){
        this.x = x;
        this.y = y;
    }

    public Point(){
        this(0,0);

    }

    public String toString() {
        return "Point x " + this.x + " y " + this.y;
    }


    public static void main(String args[]) {
        Point p2 = new Point();
        System.out.println(p2);

        Boolean b = null;
        System.out.println(b? true: false); //Exception in thread "main" java.lang.NullPointerException


    }
}
