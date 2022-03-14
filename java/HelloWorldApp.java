import java.util.*;
import java.lang.Runtime;

import HelloWorldApp.MySecondClass; 

public class HelloWorldApp {
    
    public static void main(String[] args) 
    { 
       Runtime something = Runtime.getRuntime();
       long memort1;
      System.out.println("Hello, World");
        
       Date today = new Date();
        System.out.println(today); 

       
       MySecondClass.foo1(); 
      /*  MySecondClass.foo2();   */
       int j = 0;
    
     
     List<int[]> arrayList = new ArrayList<int[]>();
    
     for(int i = 0; i <1000; i++)
     {
        int[] hundK = new int[100000];
        for(; j< 100000; j++)
        {
           hundK[j] = j*10;
        }
        
        arrayList.add(i, hundK);
       
     }
    /*  System.out.println(arrayList); */
     System.out.println("total memory is: "+ something.totalMemory());
     memort1 = something.freeMemory();
     System.out.println("init free memory is: "+ memort1);
     something.gc();
     memort1 = something.freeMemory();
     System.out.println("free memory after gc is: "+ memort1);
    
      
     Recursive(1);
    }
   
   static void Recursive(int something)
   {
      if(100 == something)
      {
         
         return;
      }
         
    System.out.print(something + " " );
      Recursive(++something);
   }
}



