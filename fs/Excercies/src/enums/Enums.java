package enums;

public class Enums {
    public enum EWeekDay {
        SUNDAY(1),
        MONDAY(2),
        TUE(3),
        WED(4),
        THR(5),
        FRI(6),
        SAT(7);

        static int getIntValue(EWeekDay a){
            return a.ordinal() + 1;
        }

        private final int day;

        private EWeekDay(int day) {
            this.day = day;
        }

    public String fromValue(int day) {
        switch (day) {
            case (1):
                System.out.println("SUNDAY");
                break;
            case (2):
                System.out.println("MONDAY");
                break;
            case (3):
                System.out.println("TUE");
                break;
            case (4):
                System.out.println("WED");
                break;
            case (5):
                System.out.println("THU");
                break;
            case (6):
                System.out.println("FRI");
                break;
            case (7):
                System.out.println("SAT");
                break;
        }
        return "GoodBye!\n";
    }
    public static void PrintAll(){
        for(EWeekDay week : EWeekDay.values()){
            System.out.print(week+ " ");
        }
        System.out.println(" ");
    }


    }
    public static void test(){


        EWeekDay test = EWeekDay.TUE;
        System.out.println(test.fromValue(6));
        EWeekDay.PrintAll();
        System.out.println(EWeekDay.getIntValue(EWeekDay.MONDAY));
        System.out.println(EWeekDay.getIntValue(EWeekDay.SAT));


    }
    public static void main(String args[]){
        Enums.test();
    }
}