import java.util.Scanner;

public class Grocery {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        
        double price = 67.69;

        System.out.println("price is $" + price);
        System.out.println("Please provide payment method: ");
        System.out.println("1 Cash, 2 Credit");
        int payment_method = scan.nextInt();

        if (1 == payment_method){
            System.out.println("how much to charge?");
            double cash = scan.nextDouble();
            double remainder = Cashier.payment(cash, price);
            
            if (0 > remainder){
                System.out.println("please add $" + (-remainder));
            }
            else{
                System.out.println("Your change is $" + remainder);
            }
        }
        else if (2 == payment_method){
            CreditCard card = new CreditCard(100);
            Cashier.payment(card, price);
            System.out.println("Greetings " + card.getCardHolder());
            System.out.println("Your credit card balance is $" + CreditCard.getBalance());

        }
        scan.close();
    }
}
