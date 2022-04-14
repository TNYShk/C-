package il.co.ilrd.factory;


import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.function.Function;

public class factoryTest {

    @Test
    void TreePrintTest(){
        PrintTree offer = new PrintTree("/home/tanya/git/fs");
        offer.tree();
    }

    @Test
    void TearsTestAnonymous(){
        TearFactory<Integer,TearTest,Integer> tears = new TearFactory<>();
        tears.add(new TearTest(590).cry,27);
        tears.add(new TearTest(),26);
        TearTest one = tears.create(27,26);
        TearTest two = new TearTest(5);
        tears.add(one.apply(111),28);
        tears.add(two,29);
        TearTest three = tears.create(26);
        tears.create(26).cryAlot();
        one.cryAlot();
        two.cryAlot();
        TearTest four =  new TearTest(null);
        tears.add(four,null);

        tears.create(28).cryAlot();
        three.cryAlot();
        three.cryAlot();
        three.cryAlot();
        three.print();
      assertEquals(0,four.howManyTears());
        assertEquals(29,three.howManyTears());
        assertEquals(5, tears.mapSize());
        Function<Integer,TearTest> Anonymus = new Function<Integer, TearTest>() {
            @Override
            public TearTest apply(Integer integer) {
                return new TearTest(three.howManyTears());
            }
        };
        tears.add(Anonymus,1);

        System.out.println("\nAnonymous class");
        tears.create(1).cryAlot();
        tears.create(1).printW().cryAlot();

        System.out.println("\ntest 4? or 5?");
        tears.add(TearTest::printWow,3);
        TearTest a1 = tears.create(3);
        tears.add(a1,4);
        tears.create(4).printW();
        System.out.println("size is " + tears.mapSize());

    }
    @Test
     void staticLambda(){
        TearFactory<Integer, TearTest.Shiraz,String> statTest = new TearFactory<>();
        statTest.add(TearTest.Shiraz.talk, 1);
        statTest.add(TearTest.Shiraz.talks, 2);
        statTest.add(TearTest.Shiraz.staticTalk, 3);
        TearTest.Shiraz shiri = statTest.create(1,"Shiraz");
        assertEquals("Shiraazzzzzz", TearTest.Shiraz.getName());
        TearTest.Shiraz shigi = statTest.create(2);
        assertEquals("Shiraazzzzzz", TearTest.Shiraz.getName());
        TearTest.Shiraz shibi = statTest.create(3,"data");
        assertEquals("another", TearTest.Shiraz.getName());

    }
    public static void main(String []args) {

    }

}
