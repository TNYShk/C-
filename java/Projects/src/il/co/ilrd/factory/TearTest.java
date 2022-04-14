package il.co.ilrd.factory;

import java.util.function.Function;

public class TearTest implements Function<Integer,TearTest> {
    private Integer tearsNumber;
    static int wow = 6;

    public TearTest(Integer tearsNumber){
        this.tearsNumber = tearsNumber;
    }
    public TearTest(){
        this.tearsNumber = 26;
    }
    public void prnt(){
        System.out.println("so far tears cried: "+ (++tearsNumber));
    }
    public static TearTest printWow(Integer n){
        System.out.println("static tears " + (++wow));
        return new TearTest(wow);
    }

    public  TearTest printW(){
        System.out.println("non static tears " + (++wow));
        return new TearTest(wow);
    }

    public Function<Integer,TearTest> cry = (tearsNumber) -> { System.out.println("lambda?"); return new TearTest(tearsNumber);};


    @Override
    public TearTest apply(Integer integer) {
        if(integer == null){
            return new TearTest();
        }
        System.out.println("apply?");
       return new TearTest(integer);
    }

    static class Shiraz{
        static String name;

        public Shiraz(){
            name = "Shiraazzzzzz";
        }
         public Shiraz(String name){
             Shiraz.name = name;
         }

         public static void getName(){
            System.out.println(Shiraz.name);
         }


        public static Function<String, Shiraz> talk = (String s) -> {System.out.println("static lambda!"); return new Shiraz("tt");};
         public static Function<String, Shiraz> talks = (String s) -> {System.out.print("recursive? lambda! "); return  Shiraz.talk.apply("");};



     }
}
