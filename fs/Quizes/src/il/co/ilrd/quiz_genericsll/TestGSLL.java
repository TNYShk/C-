package il.co.ilrd.quiz_genericsll;

import org.junit.Assert;
import org.junit.Test;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

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

      test.printGenList();

   }

   @Test
    public void testDos(){
       GenericLinkedList<Number> dos = new GenericLinkedList<>();
       dos.pushFront(1);
       dos.pushFront(21);
       dos.pushFront(321);
       dos.pushFront(4321);
       dos.printGenList();

       dos.reverseList();
       System.out.println();
       dos.printGenList();
       System.out.println();
       dos.flipList();
       dos.printGenList();

    }

    @Test
    public void testTres(){
        GenericLinkedList<Number> dos = new GenericLinkedList<>();
        dos.pushFront(1);
        dos.pushFront(21);
        dos.pushFront(321);
        dos.pushFront(4321);
        dos.pushFront(54321);
        dos.printGenList();

        System.out.println(dos.getNthFromEnd(1));
        System.out.println(dos.getNthFromEnd(2));
        dos.printGenList();
        dos.circularShiftInPlace(2);
        dos.printGenList();
        dos.circularShiftInPlace(1);
        dos.printGenList();


    }

}
