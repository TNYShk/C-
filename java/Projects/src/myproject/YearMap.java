package myproject;

import java.io.IOException;
import java.nio.file.NoSuchFileException;
import java.text.ParseException;
import java.time.LocalDate;

import java.time.YearMonth;
import java.time.temporal.ChronoUnit;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;




public class YearMap {
    private static ImportCSV allData;
    private static List<Row> ofYears;

    private final String[]months = {" ","Jan","Feb","Mar", "Apr","May","June","July","Aug","Sep","Oct","Nov","Dec"};


    YearMap() throws NoSuchFileException {
        allData = new ImportCSV("/Users/tanyashkolnik/git/java/Projects/src/myproject/rent_data.csv");
    }


    private int allOffices(){
        int offices = 0;
        for(int i = 0 ; i < allData.data.size(); ++i){
            offices += allData.data.get(i).getCapacity();
        }
        return offices;
    }
    public void sumYearCapacity(int year){
        int totalCapacity = 0;

        for(int i =0; i< allData.data.size();++i){
            if(allData.data.get(i).getStartYear() == year || ((allData.data.get(i).getStartYear() < year) && (allData.data.get(i).getEndYear() >= year))){
                totalCapacity +=allData.data.get(i).getCapacity();
            }
        }
        System.out.println("unreserved offices: " + (allOffices() - totalCapacity));
    }
    abstract static class Logger{
        static Map<Integer,List<Row>> logger = new HashMap<>();
        abstract void addData(int year, List<Row>data);

    }
    public static void initYearBook(int year){
        ofYears = new LinkedList<>();
        for(int i = 0;i < allData.data.size() && year >= allData.data.get(i).getStartYear();++i){
            if(allData.data.get(i).getStartYear() == year || ((allData.data.get(i).getStartYear() < year) && (allData.data.get(i).getEndYear() >= year))){
                ofYears.add(allData.data.get(i));
            }
        }

        Logger log = new Logger(){
            @Override
            void addData(int year, List<Row> data) {
                logger.put(year,ofYears);
            }
        };
    }

    public int calculateRevenue(int year, int month){
        int revenue = 0;
        int currentCapacity = 0;
        initYearBook(year);

        if(!checkParams(year,month)){
            System.out.println("Revenue for the month of "+months[month]+ ", "+year+" is "+ sumAllRevenue()+"$");
            sumYearCapacity(year);
           return sumAllRevenue();
        }
        LocalDate pivot = LocalDate.of(year,month,getDaysInMonth(year,month));
        for (Row ofYear : ofYears) {

            long pivotStart = ChronoUnit.DAYS.between(ofYear.getStart(), pivot) +1;
            long pivotEnd = ChronoUnit.DAYS.between(ofYear.getEnd(), pivot);
            if(pivotStart>0 && (pivotEnd <= 0)){
                currentCapacity += ofYear.getCapacity();
            }

            //System.out.println(ofYear.getStart()+"  "+ ofYear.getEnd());

            /*System.out.println("start "+pivotStart);
            System.out.println("end "+ pivotEnd);
            System.out.println();*/
            if(pivotStart >= getDaysInMonth(year,month) && (pivotEnd <= 0)){
                revenue += ofYear.getPrice();
            }else if((pivotStart > 0 ) && (pivotStart < getDaysInMonth(year,month)) && (pivotEnd <= 0)){
                double ratio = ((double)pivotStart / (getDaysInMonth(year, month)));

                revenue += (ratio * ofYear.getPrice());
            }

        }
        System.out.println("revenue for the month of "+months[month]+ ", "+year+" is "+ revenue+"$");
        System.out.println("Reserved offices "+ currentCapacity + " out of "+ allOffices());
        return revenue;
    }
    private int sumAllRevenue(){
        int revenue = 0;

        for (Row ofYear : ofYears) {
            revenue += ofYear.getPrice();
        }
        return revenue;
    }


    private int getDaysInMonth(int year,int month){
        YearMonth yearMonthObject = YearMonth.of(year, month);
        return yearMonthObject.lengthOfMonth();
    }

    public boolean checkParams(int year, int month){
        if((month < 1 || month >12) || (year > java.time.LocalDate.now().getYear()))
            throw new RuntimeException("bad input!");
        return year <= 2015;

    }
    public void InitializeIt() throws IOException {
        ImportCSV.readFromCSV(allData.data, allData.pathToFile);
    }



    public static void main(String[] args) throws IOException, ParseException {
        YearMap testing = new YearMap();
        ImportCSV.readFromCSV(allData.data, allData.pathToFile);

        //initYearBook(2014);
        //System.out.println(ofYears);
        //System.out.println(testing.sumAllRevenue());
       // System.out.print("\n\n" + allData.data+"\n");

      /*



      */
        testing.calculateRevenue(2014,9); //correct is 86700$ 144 offices reserved
        //testing.calculateRevenue(2018,1); //correct 75500
       //testing.calculateRevenue(2015,7); //correct is 76250$
       //testing.calculateRevenue(2013,1); //correct 8100$
        //testing.calculateRevenue(2014,3);// correct 37214$ 63 offices reserved
        testing.calculateRevenue(2000,1); // correct 0$
        //testing.calculateRevenue(2013,6);// correct 15150$

        //System.out.println("reserved offices: "+testing.sumYearCapacity(2018));

    }
}
