package il.co.ilrd.quiz_genericsll;

import org.junit.Assert;
import org.junit.Test;

import java.util.Iterator;

public class TestGSLL {

   @Test
    public void testuno(){
      GenericLinkedList<String> test = new GenericLinkedList<>();
      Assert.assertTrue(test.isEmpty());
      String hi = "Hi";
      test.pushFront(hi);
      String get = test.popFront();
      Assert.assertEquals(hi,get);

       test.pushFront("tanya");
       test.pushFront("is");
       test.pushFront("name");
      test.pushFront("my");
       test.pushFront(hi);


      Iterator<String> find = test.find("is");
        System.out.println(find);
      Assert.assertNotNull(find);

      Assert.assertEquals(5,test.size());
      for(String s: test){
          System.out.print(s+" ");
      }



   }
}
