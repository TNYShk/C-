package il.co.ilrd.factory;

import java.util.function.Function;

public class TearTest implements Function<Integer,TearTest> {
    private final Integer tearsNumber;


    public TearTest(Integer tearsNumber){
        this.tearsNumber = tearsNumber;

    }
    public TearTest(){
        this.tearsNumber = 26;

    }

    public Function<Integer,TearTest> cry = (tearsNumber) -> { System.out.println("lambda?"); return new TearTest(tearsNumber);};


    @Override
    public TearTest apply(Integer integer) {
        System.out.println("apply?");
       return new TearTest(integer);
    }

     static class Shiraz{
        static String name;

        public Shiraz(){
            name = "Shiraazzzzzz";
        }
        public static String getName(){
            return name;
        }

        public static Function<String, Shiraz> talk = (String s) -> {System.out.println("static lambda!"); return new Shiraz();};
         public static Function<String, Shiraz> talks = (String s) -> {System.out.print("recursive? lambda! "); return  Shiraz.talk.apply("");};
    }
}
