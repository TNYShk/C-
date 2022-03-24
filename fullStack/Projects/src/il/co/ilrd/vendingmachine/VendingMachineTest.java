package il.co.ilrd.vendingmachine;

import sun.awt.X11.Screen;

public class VendingMachineTest {
    public static void main(String[] args) {
        Products[] catalog = Products.values();
        ScreenIMP scream = new ScreenIMP();
        VendingMachine vm = new VendingMachine(catalog, scream);

        vm.turnON();
        vm.insertCoin(Coins.TENS);

        vm.chooseProduct(Products.COLA);
        vm.insertCoin(Coins.TENS);
        vm.cancelReturn();
        vm.turnOFF();
        vm.turnON();
        vm.insertCoin(Coins.TENS);
        vm.insertCoin(Coins.TENS);
        vm.chooseProduct(Products.BEER);
        vm.insertCoin(Coins.FIVES);
        vm.insertCoin(Coins.SHEKEL);
        vm.chooseProduct(Products.POISON);
        vm.insertCoin(Coins.TENS);
        vm.insertCoin(Coins.HALFS);
        vm.insertCoin(Coins.HALFS);
        vm.chooseProduct(Products.CANDY);
        vm.chooseProduct(Products.COFFEE);
        vm.insertCoin(Coins.AGORA);
        vm.cancelReturn();
        vm.insertCoin(Coins.TENS);
        vm.chooseProduct(Products.WATER);
        vm.turnOFF();
    }
}
