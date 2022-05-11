package il.co.ilrd.factory;


import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.function.Function;

public class FactoryTest {

    @Test
    void TreePrintTest(){
        PrintTree offer = new PrintTree("/home/tanya/git/fs");
        offer.tree();
    }

    @Test
    void TearsTest(){
        Factory<Integer, TearFactory,Integer> tears = new Factory<>();
        tears.add(new TearFactory(590).cry,27);
        tears.add(new TearFactory(),26);
        TearFactory one = tears.create(26,260);
        TearFactory two = new TearFactory(5);
        tears.add(one.apply(111),28);
        tears.add(two,29);
        TearFactory three = tears.create(26);
        TearFactory another = tears.create(27,270);
        another.print();
        another.apply(0);

        tears.create(27).print();
        one.cryAlot();
        two.cryAlot();
        TearFactory four =  new TearFactory(null);
        tears.add(four,null);
        tears.create(28).cryAlot();
        three.cryAlot();
        three.cryAlot();
        three.cryAlot();
        three.print();
        assertEquals(0,four.howManyTears());
        assertEquals(29,three.howManyTears());
        assertEquals(5, tears.mapSize());

        System.out.println("\ntest 4 & | 5");
        tears.add(TearFactory::printWow,3);

        TearFactory a1 = tears.create(3);
        tears.add(a1,4);
        tears.create(4).printW();

        assertEquals(7, tears.mapSize());

    }
    @Test
    void Anonym(){
        System.out.println("\nAnonymous class");
        Factory<Integer, TearFactory,Integer> annoying = new Factory<>();
        Function<Integer, TearFactory> Anonymus = new Function<Integer, TearFactory>() {
            @Override
            public TearFactory apply(Integer integer) {
                return new TearFactory();
            }
        };
        annoying.add(Anonymus,1);

        annoying.create(1).cryAlot();
        annoying.create(1).printW().cryAlot();


        annoying.add(TearFactory::printWow,3);
        TearFactory a1 = annoying.create(3);
        annoying.add(a1,4);
        annoying.create(4).printW();
        assertEquals(3,annoying.mapSize());

    }
    @Test
     void staticLambda(){
        Factory<Integer, TearFactory.Shiraz,String> statTest = new Factory<>();

        statTest.add(TearFactory.Shiraz.talk, 1);
        statTest.add(TearFactory.Shiraz.talks, 2);
        statTest.add(TearFactory.Shiraz.staticTalk, 3);
        statTest.add((name) -> new TearFactory.Shiraz(name),4);
        TearFactory.Shiraz shiri = statTest.create(1,"Shiraz");
        assertEquals("Shiraazzzzzz", TearFactory.Shiraz.getName());
        TearFactory.Shiraz shigi = statTest.create(2);
        assertEquals("Shiraazzzzzz", TearFactory.Shiraz.getName());
        TearFactory.Shiraz shibi = statTest.create(3,"data");
        assertEquals("another", TearFactory.Shiraz.getName());
        TearFactory.Shiraz shurum = statTest.create(4,"gurum");
        assertEquals(4,statTest.mapSize());

        assertEquals("gurum", TearFactory.Shiraz.getName());


    }
    public static void main(String []args) {

    }

}
