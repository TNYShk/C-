package il.co.ilrd.vendingmachine;
import com.sun.corba.se.impl.oa.toa.TOA;

import java.awt.*;
import java.util.Timer;
import java.util.TimerTask;

public class VendingMachine{
    private State state = State.OFF;
    private final Products[] catalogMachine;
    public double balance = 0;
    private final Screen myScreen;
    private Products chosenProduct = Products.EMPTY;
    Toolkit tools;
    Timer timer;
    private long secondsToWait = 10;


    public VendingMachine(Products[] catalogMachine, Screen myScreen){
        this.catalogMachine = catalogMachine;
        this.myScreen = myScreen;
        this.balance = 0;
        timer = new Timer();
        tools = Toolkit.getDefaultToolkit();

    }
    class RemindTask extends TimerTask {
        public void run(){
            if (secondsToWait > 0) {
               //tools.beep();
                --secondsToWait;
                turnON();
            }else{
                tools.beep();
                System.out.println("no input, good bye!");
                cancelReturn();
                timer.cancel();
            }

        }
    }

    public void insertCoin(Coins coin) {
      this.secondsToWait = 10;
        state.insertCoin(this, coin);
    }

    public void chooseProduct(Products desired) {
        chosenProduct = desired;
       timer.scheduleAtFixedRate(new RemindTask(), secondsToWait,5000);
       state.chooseProduct(this,desired);
    }

    public void cancelReturn() {
        chosenProduct = Products.EMPTY;
        state.cancelReturn(this);
    }

    public void turnOFF() {
        state.turnOFF(this);
    }
    public void turnON() {
        state.turnON(this);
    }

    private enum State {
        OFF {
            @Override
            public void turnON(VendingMachine mac) {
                mac.myScreen.Print("\nON and Ready!");
                mac.state = WAITPRODUCT;
            }
        },

        WAITPRODUCT {
            @Override
            public void insertCoin(VendingMachine mac, Coins coin) {
                mac.balance += coin.getValue();
                mac.instance.Print("current balance: " + mac.balance);
            }

            @Override
            public void chooseProduct(VendingMachine mac, Products chosen) {
                mac.chosenProduct = chosen;
                double left = mac.balance - mac.chosenProduct.getPrice();
                mac.instance.Print("you chose " + mac.chosenProduct.getName() + " costs: "+ mac.chosenProduct.getPrice());

                if (0 > left) {
                    mac.myScreen.Print("not enough, you're missing " + -left);
                    mac.state = WAITCOINS;
                } else {
                    mac.instance.Print("here's your " + mac.chosenProduct.getName() + " and change, if any " + left);
                    mac.balance = 0;
                }
            }
        },
        WAITCOINS {
            @Override
            public void insertCoin(VendingMachine mac, Coins coin) {
                mac.balance += coin.getValue();
                mac.myScreen.Print("current balance: " + mac.balance);
                mac.myScreen.Print("you chose " + mac.chosenProduct.getName() + " costs: "+ mac.chosenProduct.getPrice());
                double left = mac.balance - mac.chosenProduct.getPrice();
                if (0 > left) {
                    mac.myScreen.Print("not enough, you're missing " + -left);
                } else {
                    mac.myScreen.Print("here's your " + mac.chosenProduct.getName() + " and change, if any " + left);
                    mac.balance = 0;
                }
            }

            @Override
            public void chooseProduct (VendingMachine mac, Products chosen){
                mac.chosenProduct = chosen;
                mac.myScreen.Print(" "+ mac.chosenProduct.getName() + " costs " + mac.chosenProduct.getPrice());
                if(mac.balance >= mac.chosenProduct.getPrice()) {
                    mac.balance -= mac.chosenProduct.getPrice();
                    if (mac.balance != 0) {
                        mac.myScreen.Print("here's your change " + mac.balance);
                    }
                    mac.myScreen.Print("Enjoy your " + mac.chosenProduct.getName());
                    mac.balance = 0;
                    mac.state = WAITPRODUCT;
                }
                mac.myScreen.Print("not enough, you're missing " + (mac.chosenProduct.getPrice() - mac.balance));
            }

        };

       // private Screen instance;

        public void insertCoin(VendingMachine vm, Coins coin) {}

        public void chooseProduct(VendingMachine vm, Products product) {}

        public void cancelReturn(VendingMachine mac) {
            mac.state = WAITPRODUCT;
            mac.instance.Print("here's your money back " + mac.balance);
            mac.balance = 0;
        }

        public void turnOFF(VendingMachine mac) {
            if (mac.balance != 0) {
                mac.myScreen.Print("here's your change " + mac.balance);
            }

            mac.instance.Print("\nTurning OFF, GoodBye");
            mac.balance = 0;
            mac.chosenProduct = Products.EMPTY;
            mac.state = OFF;
        }

        public void turnON(VendingMachine vm) {}
    }

    Screen instance = toPrint -> System.out.println(toPrint);
/*
    static class Inner{

        void method(VendingMachine vm){
            Products statProd = Products.BEER;
            System.out.println(statProd.getName());
            System.out.println("balance is: " + vm.balance);
            System.out.println(vm.state);
        }
    }
*/
}
