package il.co.ilrd.quiz_nonrepeatsequence;

import java.util.*;

import org.junit.jupiter.api.Test;





public class FirstNonDuplicateSequence {
   static LinkedHashMap<Long,Integer> map = new LinkedHashMap<>();
   static List<Long> out = new ArrayList<>();
   static long holder = 0;

   public void input(long N){
       map.merge(N,1,Integer::sum);
       if(out.isEmpty()){
           out.add(N);
           return;
       }

       if(out.get(out.size() - 1) == N) {
           boolean found = false;
           for(Long run: map.keySet()){
               if(map.get(run) == 1){
                   out.add(run);
                   map.merge(run,1,Integer::sum);
                   found = true;
               }
           }
           if(!found){
               out.add(holder);
               holder = N;
           }
       }
       else if(out.get(out.size() - 1) != N){
           out.add(out.get(out.size() - 1));
       }


    }



    public void printOut(){
      System.out.println(out);
    }

    public long output(){
       return out.remove(0);
    }

    public static void main(String[] args) {

    }
        @Test
        public void quizQ(){
            FirstNonDuplicateSequence test = new FirstNonDuplicateSequence();

            test.input(1);
            test.input(2);
            test.input(2);
            test.input(3);
            test.input(3);
            test.input(4);
            test.input(1);
            test.input(1);
            test.input(1);
            test.input(4);
            test.input(5);


            //test.printOut();
            //System.out.println();


        }




    @Test
    public void Meital(){
        FirstNonDuplicateSequence test = new FirstNonDuplicateSequence();
        test.input(5);
        test.input(2);
        test.input(3);
        test.input(4);
        test.input(5);
        test.input(2);
        test.input(3);
        test.input(4);
        test.input(8);

        test.printOut();
        System.out.println();
       while(!test.out.isEmpty())
            System.out.print(test.output() + " ");


    }
}
