package il.co.ilrd.framework;

public enum WeekDays {
    SUNDAY("Sunday"),
    MONDAY("Monday"),
    TUESDAY("Tuesday"),
    WEDNESDAY("Wednesday"),
    THURSDAY("Thursday"),
    FRIDAY("Friday"),
    SATURDAY("Saturday");


    private final String names;

    WeekDays(String names) {
    this.names = names;

    }
    public String getDay(){
        return names;
    }
    public static void PrintAll(){
        for(WeekDays day : WeekDays.values()){
            System.out.print(day + " ");
        }
        System.out.println(" ");
    }
}
