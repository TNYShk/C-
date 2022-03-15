import java.util.Scanner;

public class Grocery {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        Cashier kupa = new Cashier();
        double price = 67.69;

        System.out.println("price is $" + price);
        System.out.println("Please provide payment method: ");
        System.out.println("1 Cash, 2 Credit");
        int payment_method = scan.nextInt();

        if (1 == payment_method){
            System.out.println("how much to charge?");
            double cash = scan.nextDouble();
            double remainder = kupa.payment(cash, price);
            
            if (0 > remainder){
                System.out.println("please add $" + (-remainder));
            }
            else{
                System.out.println("Your change is $" + remainder);
            }
        }
        else if (2 == payment_method){
            CreditCard card = new CreditCard(100);
            kupa.payment(card, price);
            System.out.println("Greetings " + card.getCardHolder());
            System.out.println("Your credit card balance is $" + card.getBalance());

        }
        short s1 = 1;
        short s2 = 3;
        short s3 = (short)(s1&s2);
        System.out.println("val is "+ s3); //error: incompatible types: possible lossy conversion from int to short

        int[] arr = {1,2,3};
        System.out.println("arr out of boundry" + arr[3]);
    }
}
