package quiz_sort_stack;

import java.util.Stack;

public class quiz_stack_sort {

    public static void sortStackAscending(Stack<Integer> stackSort){
        Stack<Integer> auxStack = new Stack<>();

        while(!stackSort.isEmpty()){
            Integer peek = stackSort.pop();
            while(!auxStack.isEmpty() && (peek < auxStack.peek())){
                stackSort.push(auxStack.pop());
            }
            auxStack.push(peek);
        }
        while(!auxStack.isEmpty())
       stackSort.push(auxStack.pop());

    }

    public static void sortRecStack(Stack<Integer> toSort){

        if(toSort.isEmpty()) return;
        Integer peek = toSort.pop();

        sortRecStack(toSort);

        insertBack(toSort,peek);
    }

    public static void insertBack(Stack<Integer> stack, int peek){
        while(!stack.isEmpty() && stack.peek()< peek){
            Integer temp = stack.pop();
            insertBack(stack,peek);
            stack.push(temp);
            return;
        }
        stack.push(peek);
    }
    public static void printStack(Stack<Integer> stack){
       while(!stack.isEmpty())
            System.out.print(stack.pop()+" ");
    }

    public static void main(String[] args){
        Stack<Integer> ss = new Stack<>();
        ss.push(34);
        ss.push(3);
        ss.push(31);
        ss.push(98);
        ss.push(92);
        ss.push(23);
    //sortStackAscending(ss);
    sortRecStack(ss);
        printStack(ss);
    }

}
