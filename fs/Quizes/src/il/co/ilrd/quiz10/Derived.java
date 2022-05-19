package il.co.ilrd.quiz10;

public class Derived extends Base{
String ds1;
int x;
    public Derived(){
        this.ds1 = "Derived";
        System.out.println("in Derived");
    }
    @Override
    public String getName() {
        return this.ds1;
    }

    public void foo(){
        System.out.println("in Override 'foo' " + ds1);
    }

    public static void main(String[] args){
    Base ab = new Derived();
    }
}
