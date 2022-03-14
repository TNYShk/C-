package HelloWorldApp; 

public class MySecondClass {
    
    public static void foo1() {
        
        System.out.println("Something Dark");
    }  
    
   /*  void foo2(){
        System.out.println("Something Light"); */
    
    public static void Recursive(int something){
      
        if(100 == something){
        System.out.print(something + " " );
        return;
    }
         
    System.out.print(something + " " );
    Recursive(something +1 );
   }
}
