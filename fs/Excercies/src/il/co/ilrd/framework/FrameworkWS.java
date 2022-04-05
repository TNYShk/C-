package il.co.ilrd.framework;


import java.util.ArrayList;
import java.util.Collections;
import java.util.*;


  public class FrameworkWS<V extends Enum<V>>  {
    static int []primar = {'t','a','n','y','a'};

    public final WeekDays[] weeks;


    Map<Integer, WeekDays> wee = new HashMap<>();

      public FrameworkWS(WeekDays[] weeks) {
          this.weeks = weeks;
      }


      public static void primitiveArr(){
        int [] arik = {12,47,66,58,10};

       /* System.out.println(Arrays.toString(FrameworkWS.primar));
        System.out.println(Arrays.toString(arik));*/

       List<Integer> list1 = new ArrayList<>();
       List<String> lists = new ArrayList<>();

        for( int i: arik){
            list1.add(i);
        }
        for( int i: FrameworkWS.primar){
            lists.add(i + " ");
        }

        System.out.println("String list:\n" + lists);
        Collections.sort(lists);
        System.out.println(Collections.min(lists));
        System.out.println("sorted String list:\n" + lists);
        System.out.println();
        System.out.println("Integer list:\n" + list1);
        Collections.sort(list1);
        System.out.println("sorted Integer list:\n" + list1);

    }

        public void createMap(){
          Map<Integer, String> wee = new HashMap<>();
          for (WeekDays i: WeekDays.values()) {
            wee.put(i.ordinal() +1 ,i.getDay());
          }

        System.out.println(wee);
    }




    public static void main(String []args){
        //primitiveArr();
       WeekDays.PrintAll();

        FrameworkWS shoshana = new FrameworkWS(WeekDays.values());
        shoshana.createMap();

        }


}
