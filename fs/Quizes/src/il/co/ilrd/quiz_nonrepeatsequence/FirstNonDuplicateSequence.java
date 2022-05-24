package il.co.ilrd.quiz_nonrepeatsequence;

import java.util.Deque;
import java.util.LinkedList;
import java.util.Stack;
import org.junit.jupiter.api.Test;



import static org.testng.AssertJUnit.assertEquals;

public class FirstNonDuplicateSequence {
    Stack<Long> stack = new Stack<>();
    Deque<Long> uniq = new LinkedList<>();
    static long holder = 0;

   public void input(long N){
        if(stack.isEmpty()){
            stack.push(N);
            uniq.add(N);
        }
        else{
            if( N != stack.peek() ){
                stack.push(stack.peek());

                if(uniq.peek() != N){
                    holder = N;
                    uniq.push(N);

                }
                else if(uniq.peek() == N){
                    holder = 0;
                    uniq.push(uniq.pollLast());
                    uniq.push(N);
                }
            }else if(N == stack.peek()){
                stack.push(holder);
            }
        }

    }



    public void printDQ(){
      System.out.print(uniq);
    }

    public long output(){
        return stack.pop();
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

            test.printDQ();
            System.out.println();
            //System.out.println(test.uniq.peekFirst());
            //System.out.println(holder);
            while(!test.stack.isEmpty()){
                System.out.print(" "+test.output());
            }
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

        test.printDQ();
        System.out.println();
        while(!test.stack.isEmpty()){
            System.out.print(" "+test.stack.pop());
        }

    }
}
