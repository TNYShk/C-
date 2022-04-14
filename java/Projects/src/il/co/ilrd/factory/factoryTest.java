package il.co.ilrd.factory;


import java.util.function.Function;

public class factoryTest {

    public static void main(String []args){
        TearFactory<Integer,TearTest,Integer> test = new TearFactory<>();
        test.add(new TearTest(590).cry,27);
        test.add(new TearTest(),26);
        TearTest one = test.create(27,26);
        TearTest two = new TearTest(5);
        TearTest three = test.create(26);
        System.out.println(one.getClass());
        one.prnt();
        two.prnt();
        three.prnt();
        three.prnt();
        three.prnt();


        /* Anonymous class*/
        Function<Integer,TearTest> Anonymus = new Function<Integer, TearTest>() {
            @Override
            public TearTest apply(Integer integer) {
                return new TearTest(570);
            }
        };
        test.add(Anonymus,1);
        /* test 4? or 5?*/

        System.out.println("Anonymous class");
        test.create(1).prnt();
        System.out.println("test 4? or 5?");
        test.add(TearTest::printWow,3);
        TearTest a1 = test.create(3);
        test.add(a1,4);
        test.create(4).printW();


        /* Static method & lambda*/
        TearFactory<Integer, TearTest.Shiraz,String> statTest = new TearFactory<>();
        statTest.add(TearTest.Shiraz.talk, 1);
        statTest.add(TearTest.Shiraz.talks, 2);
        statTest.create(1);
        statTest.create(2);



    }
}
