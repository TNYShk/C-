package tcode;

import java.util.*;

public class SmallestDifference {

    public static int findSmellestDif(int[]a, int[]b){

      Arrays.sort(a);
      Arrays.sort(b);

      int i = 0;
      int j = 0;
      int currentMin = a[a.length-1];
    while(i<a.length && j<b.length){
        int dif = Math.abs(a[i] - b[j]);
        if(dif < currentMin)
           currentMin = dif;
          if(dif == 0){
             return 0;
          }
         else if(a[i]<b[j]){
              ++i;
          }
          else{
            ++j;
          }
      }
       int max= (Math.max(i,j));
    int min = (Math.min(i,j));

    System.out.println("idxs of smallest diff are: "+min+" "+(--max));
        //System.out.println("the according values are, in []a: "+a[i]+" in b[]: "+b[j]);
   return currentMin;

    }
    public static void main(String[] args){
        int []a = {1,3,15,11,2}; //1,2,3,11,15
        int[]b = {23,127,235,19}; // 19,23,127,235
        System.out.println(findSmellestDif(a,b));
    }
}
