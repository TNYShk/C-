package il.co.ilrd.vendingmachine;

public class VendingMachine{
    State state = State.OFF;
    private final Products[] catalogMachine;
    public double balance = 0;
    private final Screen myScreen;
    private Products chosenProduct = Products.EMPTY;


    public VendingMachine(Products[] catalogMachine, Screen myScreen){
        this.catalogMachine = catalogMachine;
        this.myScreen = myScreen;
        //this.balance = 0;
    }

    public void insertCoin(Coins coin) {
        state.insertCoin(this, coin);
    }


    public void chooseProduct(Products desired) {
        this.chosenProduct = desired;
        this.state.chooseProduct(this,desired);
    }

    public void cancelReturn() {
        this.chosenProduct = Products.EMPTY;
        this.state.cancelReturn(this);
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
                mac.myScreen.Print("current balance: " + mac.balance);
            }

            @Override
            public void chooseProduct(VendingMachine mac, Products chosen) {
                mac.chosenProduct = chosen;
                double left = mac.balance - mac.chosenProduct.getPrice();
                mac.myScreen.Print("you chose " + mac.chosenProduct.getName() + " costs: "+ mac.chosenProduct.getPrice());

                if (0 > left) {
                    mac.myScreen.Print("not enough, you're missing " + -left);
                    mac.state = WAITCOINS;
                } else {
                    mac.myScreen.Print("here's your " + mac.chosenProduct.getName() + " and change, if any " + left);
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

        public void insertCoin(VendingMachine vm, Coins coin) {
            return;
        }

        public void chooseProduct(VendingMachine vm, Products product) {
            return;
        }

        public void cancelReturn(VendingMachine mac) {
            mac.state = WAITPRODUCT;
            mac.myScreen.Print("here's your money back " + mac.balance);
            mac.balance = 0;
        }

        public void turnOFF(VendingMachine mac) {
            if (mac.balance != 0) {
                mac.myScreen.Print("here's your change " + mac.balance);
            }
            System.out.println("\nTurning OFF, GoodBye");
            mac.balance = 0;
            mac.chosenProduct = Products.EMPTY;
            mac.state = OFF;
        }

        public void turnON(VendingMachine vm) {
            return;
        }
    };


}
