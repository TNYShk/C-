package il.co.ilrd.Quizes;

import sun.util.calendar.LocalGregorianCalendar;
import java.util.Date;

abstract class Employee {
    private int ID = 0 ;
    private String name = " ";
    private Date startDate;
    private Date birthDay;


    public Employee(int ID,String employeeName, Date startDate, Date birthday ){
        this.ID = ID;
        name = employeeName;
        this.startDate = startDate;
        birthDay = birthday;
    }
    public Employee(){
        this.name = "demo";
        this.startDate = new Date();
        this.birthDay = new Date();
    }


    public int getYear() {
        return startDate.getYear();
    }


}
