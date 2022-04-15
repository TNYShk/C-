package il.co.ilrd.quiz6;
interface Person{
    default void sayHello(){
        System.out.println("helloPerson");
    }
}
interface Male{
    static void sayHello(){
        System.out.println("Hi in Male");
    }
}
public class Sam implements Person, Male {


        public static void main(String[] args){
            Sam sam = new Sam();
            Sam second = new Sam();
            sam.sayHello();
            Male.sayHello();
            second.sayHello();

        }


}
