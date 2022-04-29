package il.co.ilrd.exam;

public class Q32 {
    class B{
         enum DayOfWeek{
            SUNDAY,
            MONDAY;
            public DayOfWeek(){}
            public static DayOfWeek create(){
                return new DayOfWeek();
            }
        }
    }
}
