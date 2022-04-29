package il.co.ilrd.exam;

public class Q33 {
    protected void makeSound(){
        System.out.println("animal class making sound here! ");
    }
    Q33(){
        makeSound();
    }
}
class Dog extends Q33{
    @Override
    /*protected*/public void makeSound(){
        System.out.println(s);
    }
    private String s = "Hav Hav...";


    public static void main(String[] args){
       Dog twinky = new Dog();
        twinky.makeSound();
        Q33 test = new Dog();
        test.makeSound();
        Q33 normail = new Q33();
        normail.makeSound();
    }
}