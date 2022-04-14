package il.co.ilrd.factory;

import java.util.function.Function;

public class factoryTest {

    public static void main(String []args){
        TearFactory<Integer,TearTest,Integer> test = new TearFactory<>();

        TearFactory<Integer, TearTest.Shiraz,String> statTest = new TearFactory<>();
        test.add(new TearTest(590).cry,27);
        test.create(27);

        test.add(new TearTest(),1);
        test.create(1);

        statTest.add(TearTest.Shiraz.talk, 1);
        statTest.add(TearTest.Shiraz.talks, 2);
        statTest.create(1);


        statTest.create(2);



    }
}
