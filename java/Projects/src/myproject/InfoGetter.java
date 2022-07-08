package myproject;

import java.io.IOException;
import java.nio.file.NoSuchFileException;
import java.util.Scanner;

public class InfoGetter {

    public static boolean checkDates(int year, int month){
        if((month < 1 || month >12) || (year > java.time.LocalDate.now().getYear()))
            return false;

        return (year > 1990) && (year <= java.time.LocalDate.now().getYear());

    }
    public static void main(String[] args) throws IOException {
        YearMap testing = new YearMap();
        testing.InitializeIt();
        System.out.println("CSV Successfully loaded...\n");

        Scanner sc = new Scanner(System.in);
        System.out.println("\t\tWelcome!\n");
        boolean keepRunning = true;
        System.out.println("to Exit press invalid year");
        while(keepRunning) {
            System.out.println("Enter desired year: ");
            int year = sc.nextInt();
            if (checkDates(year, 1)) {
                System.out.println("Great, now enter desired month: ");
                int month = sc.nextInt();
                if (checkDates(year, month)) {
                    System.out.println("Thanks!");
                    System.out.println();
                    testing.calculateRevenue(year, month);
                    System.out.println();
                }
            }else{
                keepRunning = false;
                System.out.print("GoodBye");
            }
        }
    }
}
