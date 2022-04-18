package il.co.ilrd.factory;

import java.util.function.Function;

public class TearFactory implements Function<Integer, TearFactory> {
    private Integer tearsNumber;
    static int wow = 6;

    public TearFactory(Integer tearsNumber){
        if(tearsNumber != null)
            this.tearsNumber = tearsNumber;
        else{this.tearsNumber = 0;}
    }
    public TearFactory(){
        this.tearsNumber = 26;
    }
    public void cryAlot(){
        ++tearsNumber;

    }
    public void print(){

        System.out.println("so far cried "+ (tearsNumber)+ " tears");
    }
    public static TearFactory printWow(Integer n){
        System.out.println("static tears " + (++wow));
        return new TearFactory(wow);
    }

    public TearFactory printW(){
        System.out.println("non static tears " + (++wow));
        int doubleTears = wow<<1;
        return new TearFactory(doubleTears);
    }
    public Integer howManyTears(){
       return this.tearsNumber;
    }

    public Function<Integer, TearFactory> cry = (tearsNumber) -> { System.out.println("lambda"); return new TearFactory(tearsNumber);};


    @Override
    public TearFactory apply(Integer integer) {
        if(integer == null){
            return new TearFactory();
        }
        System.out.println("apply()");
       return new TearFactory(integer);
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
