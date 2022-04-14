package il.co.ilrd.factory;

import java.util.function.Function;

public class TearTest implements Function<Integer,TearTest> {
    private Integer tearsNumber;
    static int wow = 6;

    public TearTest(Integer tearsNumber){
        if(tearsNumber != null)
            this.tearsNumber = tearsNumber;
        else{this.tearsNumber = 0;}
    }
    public TearTest(){
        this.tearsNumber = 26;
    }
    public void cryAlot(){
        ++tearsNumber;

    }
    public void print(){

        System.out.println("so far cried "+ (tearsNumber)+ " tears");
    }
    public static TearTest printWow(Integer n){
        System.out.println("static tears " + (++wow));
        return new TearTest(wow);
    }

    public TearTest printW(){
        System.out.println("non static tears " + (++wow));
        int doubleTears = wow<<1;
        return new TearTest(doubleTears);
    }
    public Integer howManyTears(){
       return this.tearsNumber;
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

         public static String getName(){
            return (Shiraz.name);
         }


        public static Function<String, Shiraz> talk = (String s) -> {System.out.println("static lambda!"); return new Shiraz();};
        public static Function<String, Shiraz> staticTalk = (String s) -> {System.out.println("static lambda!"); return new Shiraz("another");};
         public static Function<String, Shiraz> talks = (String s) -> {System.out.print("recursive? lambda! "); return  Shiraz.talk.apply("");};



    }
}
