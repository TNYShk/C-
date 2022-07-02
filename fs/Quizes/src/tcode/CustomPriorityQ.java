package tcode;

import java.util.PriorityQueue;

public class CustomPriorityQ {
    PriorityQueue<someObj> PQ = new PriorityQueue<>(5);

    class someObj implements Comparable<someObj>{
        private int attrID;
        private String name;
        private int amount;

        public someObj(int id, String name, int amount){
            attrID = id;
            this.name = name;
            this.amount = amount;
        }

        @Override
        public int compareTo(someObj o) {
            return this.name.compareTo(o.name);
            //return this.attrID > o.attrID ? 1 : -1;
        }
        @Override
        public String toString(){
            return "objID: "+ this.attrID+" named: "+ this.name+" has amount of: "+this.amount +"\n";
        }
        public int getID(){
            return this.attrID;
        }
        public String getName(){
            return this.name;
        }
        public int getAmount(){
            return this.amount;
        }
    }


    public static void main(String[] args){
       CustomPriorityQ test = new CustomPriorityQ();
        someObj inner = test.new someObj(10,"1ione",11);
        someObj another = test.new someObj(200,"3ird",22);
        someObj three = test.new someObj(13,"2ieco",33);
        someObj four = test.new someObj(4,"4iour",4);
        test.PQ.add(inner);
        test.PQ.add(another);
        test.PQ.add(three);
        test.PQ.add(four);

        System.out.println(test.PQ);



    }
}
