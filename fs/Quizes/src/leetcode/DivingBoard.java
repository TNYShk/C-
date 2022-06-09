package leetcode;

import java.util.*;

public class DivingBoard {
    static List<List<Integer>> board = new LinkedList<>();
    public void fillBoard(int k, int shorty, int longy){

        for(int i= 0,j =0; i<=k;++i,j=0){
           // int j = 0;
            ArrayList<Integer> local = make(k,shorty);

            //System.out.println("j: "+j+" i "+ i);

            while(j<i){
                local.set(j, longy);
                ++j;

            }
            board.add(local);
            sumBoard(local);

        }
        print();

    }
    public void sumBoard(ArrayList<Integer>local){
        int sum = 0;
        for(int i: local)
            sum += i;
        System.out.println("local sum: "+ sum);
    }
    private ArrayList<Integer> make(int k, int fill){
        ArrayList<Integer> local = new ArrayList<>(k);
        for(int i=0;i<k;++i)
                local.add(i,fill);
        return local;
    }
    public static void print(){
        for(List<Integer> i: board){
            System.out.println(i);
        }
    }

    public static void main(String[] args){
        DivingBoard test = new DivingBoard();
        test.fillBoard(4,3,5);

    }
}
