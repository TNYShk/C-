package enums;

public class Enums {
    public enum EWeekDay {
        SUNDAY(1),
        MONDAY(2),
        TUE(3),
        WED(4),
        THURSDAY(5),
        FRIDAY(6),
        SATURDAY(7);

        static int getIntValue(EWeekDay a){
            return a.ordinal() + 1;
        }
        private static EWeekDay[] weekArray = EWeekDay.values();

        private final int day;

        EWeekDay(int day) {
            this.day = day;
        }
        public static EWeekDay returnValue(int num) {
            return weekArray[num - 1];
        }

        public static String fromValue(int day) {
        switch (day) {
            case (1):
                System.out.println(EWeekDay.valueOf("SUNDAY"));
                break;
            case (2):
                System.out.println(EWeekDay.valueOf("MONDAY"));
                break;
            case (3):
                System.out.println(EWeekDay.valueOf("TUE"));
                break;
            case (4):
                System.out.println(EWeekDay.valueOf("WED"));
                break;
            case (5):
                System.out.println(EWeekDay.valueOf("THURSDAY"));
                break;
            case (6):
                System.out.println(EWeekDay.valueOf("FRIDAY"));
                break;
            case (7):
                System.out.println(EWeekDay.valueOf("SATURDAY"));
                break;
            default:
                System.out.println("NOT VALID");
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

        System.out.println(EWeekDay.fromValue(0));
        System.out.println(EWeekDay.fromValue(1));
        System.out.println(EWeekDay.fromValue(6));
        EWeekDay.PrintAll();
        System.out.println(EWeekDay.getIntValue(EWeekDay.MONDAY));
        System.out.println(EWeekDay.getIntValue(EWeekDay.SATURDAY));

        System.out.println(EWeekDay.returnValue(2));


    }
    public static void main(String args[]){
        Enums.test();

    }
}
