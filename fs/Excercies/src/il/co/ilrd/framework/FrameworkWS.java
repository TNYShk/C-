package il.co.ilrd.framework;


import static il.co.ilrd.framework.DataObject.setObject;
import java.util.*;



public class FrameworkWS {
    static int []primar = {'t','a','n','y','a'};

    public final WeekDays[] weeks;


    Map<Integer, WeekDays> wee = new HashMap<>();

      public FrameworkWS(WeekDays[] weeks) {
          this.weeks = weeks;
      }


      public static void ex1(){
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

        public void ex2(){
          Map<Integer, String> wee = new HashMap<>();
          for (WeekDays i: WeekDays.values()) {
            wee.put(i.ordinal() +1 ,i.getDay());

          }

        System.out.println(wee);
    }




    public static void main(String []args){
        ex1();
       //WeekDays.PrintAll();

        FrameworkWS shoshana = new FrameworkWS(WeekDays.values());
        shoshana.ex2();

        Exe3();


    }
    static void Exe3(){
        DataObject [] ex3 = {
                setObject("neTanya",1),
                setObject("shoshi", 2),
                setObject("ufer", 3),
                setObject("shayke", 4),
                setObject("nuyit", 5),
                setObject("cabarneShiraz", 6),
                setObject("neTanya",-1),
                setObject("shoshi", -2),
                setObject("ufer", -3),
                setObject("shayke", -4),
                setObject("nuyit", -5),
                setObject("cabarneShiraz", -6),
        };
        for(DataObject dataObject: ex3)
            System.out.println(dataObject.getValue() + " " + dataObject.getCode() );

        Map<String, Integer> e3 = new HashMap<>();

        for (DataObject dataObject : ex3) {
            e3.merge(dataObject.getCode(), dataObject.getValue(),  Integer::sum);
        }
        System.out.println("\nsum is now:\n" + e3);
    }


}
