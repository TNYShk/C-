import java.util.*;
import java.lang.Runtime;

import HelloWorldApp.MySecondClass; 

public class HelloWorldApp {
    
   public static void main(String[] args) { 
      
      Runtime something = Runtime.getRuntime(); 
      long memort1 = 0;
      System.out.println("Hello, World!");
        
      Date today = new Date();
      System.out.println(today); 

      MySecondClass.foo1(); 
      /*  MySecondClass.foo2();   */
      
       QFiveTeen();
     
    /*  System.out.println(arrayList); */
      System.out.println("total memory is: "+ something.totalMemory()+ " bytes");
      memort1 = something.freeMemory();
      System.out.println("init free memory is: "+ memort1+ " bytes");
      something.gc();
      memort1 = something.freeMemory();
      System.out.println("free memory after gc is: "+ memort1 + " bytes");
      System.out.println(" ");
      
     MySecondClass.Recursive(0);
     System.out.println(" ");
    }
   
   public static void QFiveTeen(){

      List<int[]> arrayList = new ArrayList<int[]>();
     
      for(int i = 0; i < 1000; ++i)
      {
         int[] hundK = new int[100000];
         for(int j = 0; j < hundK.length; ++j)
         {
            hundK[j] = j*10;
         }
         
         arrayList.add(i, hundK);
      }
     
   }
}


