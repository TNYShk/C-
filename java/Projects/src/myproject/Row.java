package myproject;

import java.time.LocalDate;
import java.time.Period;


public class Row implements Comparable<Row> {
    private int capacity;
    private int price;
    private LocalDate start;
    private LocalDate end;

    private int days;
    private long months;
    private int years;
    private double dailyPrice;


    public Row(int capacity, int price, LocalDate start, LocalDate end){
        this.capacity = capacity;
        this.price = price;
        this.start = start;
        this.end = end;

        Period period = Period.between(end,start);
        days = Math.abs(period.getDays());
        months = Math.abs(period.toTotalMonths());
        years = Math.abs(period.getYears());
        dailyPrice = price / 30.0;
    }

    public LocalDate getEnd() {
        return end;
    }

    public LocalDate getStart() {
        return start;
    }

    public int getCapacity() {
        return capacity;
    }

    public int getPrice() {
        return price;
    }
    public double getDailyPrice(){
        return dailyPrice;
    }

    public int getStartYear(){
        return start.getYear();
    }
    public int getEndYear(){
        return end.getYear();
    }
    public int getStartMonth(){
        return start.getMonthValue();
    }
    public int getEndMonth(){
        return end.getMonthValue();
    }
    public int getStartDay(){
        return start.getDayOfMonth();
    }

    @Override
    public int compareTo(Row o) {
       return this.start.compareTo(o.getStart());
    }


    @Override
    public String toString(){
        //printMeta(headers);
       // return "Row [Capacity = "+getCapacity()+ " Monthly Price = "+ getPrice()+ " Start Day " + getStart()+ " End Date "+ getEnd()+"\n";
        return "\n[ "+getCapacity()+ "  ,  "+ getPrice()+ "  ,  " + getStart()+ "  ,  "+ getEnd()+" ]";
               // "\n In Total:\n\t Years: "+ years+"  Months:  "+months+ " and "+days+" days";
    }
}
