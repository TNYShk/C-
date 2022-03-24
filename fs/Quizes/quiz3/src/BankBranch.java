package il.co.ilrd.Quizes;
import sun.util.calendar.LocalGregorianCalendar;
import java.util.Date;

public class BankBranch extends Employee {
    Date date = new Date();
    private int seniority;

    public BankBranch(){
        super();
        this.seniority = 2022 - super.getYear();
    }
    protected void setID(int ID){
        super.ID = ID;
    }

    protected void setName(String empName){
        this.name = empName;
    }
}
