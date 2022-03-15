public class CreditCard {
  private static double balance;
  private String name;

  public CreditCard(double b) {
    balance = b; 
    name = "Tanya";
  }
  
  public static void debit (double amount) {
    balance = balance - amount;
  }
  
  public static void credit (double amount) {
    balance = balance + amount;
  }
  
  public static double getBalance () {
    return balance;
  }

  public String getCardHolder() {
    return name;
  }
}