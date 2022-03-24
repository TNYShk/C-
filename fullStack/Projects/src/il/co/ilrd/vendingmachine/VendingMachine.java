package il.co.ilrd.vendingmachine;

public class VendingMachine implements Screen{
    State state = State.OFF;
    private final Products[] catalogMachine;
    public double balance = 0;
    private final Screen myScreen;
    private Products chosenP = Products.EMPTY;


    public VendingMachine(Products[] catalogMachine, Screen myScreen){
        this.catalogMachine = catalogMachine;
        this.myScreen = myScreen;
        this.balance = 0;
    }

    public void insertCoin(Coins coin) {
        state.insertCoin(this, coin);
    }


    public void chooseProduct(Products desired) {
        this.chosenP = desired;
        this.state.chooseProduct(this,desired);
    }

    public void cancelReturn() {
        this.chosenP = Products.EMPTY;
        this.state.cancelReturn(this);
    }

    public void turnOFF() {
        this.balance = 0;
        state.turnOFF(this);
    }
    public void turnON() {
        state.turnON(this);
    }

    private enum State {
        OFF {
            @Override
            public void turnON(VendingMachine mac) {
                mac.state = WAITPRODUCT;
            }
        },

        WAITPRODUCT {
            @Override
            public void insertCoin(VendingMachine mac, Coins coin) {
                mac.balance += coin.getValue();
            }

            @Override
            public void turnOFF(VendingMachine mac) {
                mac.balance = 0;
                mac.state = OFF;
            }

            @Override
            public void cancelReturn(VendingMachine mac) {
                mac.state = WAITPRODUCT;
                System.out.println("here's your money back" + mac.balance);
                mac.balance = 0;
            }

            @Override
            public void chooseProduct(VendingMachine mac, Products chosen) {
                mac.chosenP = chosen;
                double left = mac.balance - mac.chosenP.getPrice();
                if (0 > left) {
                    System.out.println("not enough, you're missing " + -left);
                    mac.state = WAITCOINS;
                } else {
                    System.out.println("here's you're change if any " + left);
                    mac.balance = 0;
                }
            }
        },
        WAITCOINS {
            @Override
            public void insertCoin(VendingMachine mac, Coins coin) {
                mac.balance += coin.getValue();

                double left = mac.balance - mac.chosenP.getPrice();
                if (0 > left) {
                    System.out.println("not enough, you're missing " + -left);
                } else {
                    System.out.println("here's your" + mac.chosenP.getName() + " and change, if any " + left);
                    mac.balance = 0;
                }
            }
            @Override
            public void turnOFF (VendingMachine mac){
                if (mac.balance != 0) {
                    System.out.print("here's your change " + mac.balance);
                }
                System.out.println("GoodBye");
                mac.balance = 0;
                mac.chosenP = Products.EMPTY;
                mac.state = OFF;
            }
            @Override
            public void cancelReturn (VendingMachine mac){
                mac.balance = 0;
                mac.state = WAITPRODUCT;
            }

            @Override
            public void chooseProduct (VendingMachine mac, Products chosen){
                mac.chosenP = chosen;
                System.out.println(" "+ mac.chosenP.getName() + " costs " + mac.chosenP.getPrice());
                if(mac.balance >= mac.chosenP.getPrice()) {
                    mac.balance -= mac.chosenP.getPrice();
                    if (mac.balance != 0) {
                        System.out.print("here's your change " + mac.balance);
                    }
                    System.out.println("Enjoy your " + mac.chosenP.getName());
                    mac.balance = 0;
                    mac.state = WAITPRODUCT;
                }
                System.out.println("not enough, you're missing " + (mac.chosenP.getPrice() - mac.balance));
            }

        };

        public void insertCoin(VendingMachine vm, Coins coin) {
            return;
        }

        public void chooseProduct(VendingMachine vm, Products product) {
            return;
        }

        public void cancelReturn(VendingMachine vm) {
            return;
        }

        public void turnOFF(VendingMachine vm) {
            return;
        }

        public void turnON(VendingMachine vm) {
            return;
        }
    };


}
