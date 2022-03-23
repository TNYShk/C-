package il.co.ilrd.Quiz2;
import static java.lang.Math.PI;
// cant import Class statically for its consts, must import statically the const itself

// quiz 2 JAVA Mar 20, 2022
public class quiz2 {

    public static void main(String args[]) {
        Point p2 = new Point();
        System.out.println(p2);
        
        Bolean b = null;
        System.out.println(b? true: false); //Exception in thread "main" java.lang.NullPointerException
        

    }
    final class some{}
    private class another{}
    public class next{}

}

class Point{
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
    }

    abstract class SomeClass{}
    final class some{}
   // each public class should have its own .java file




