package il.co.ilrd.vendingmachine;

public class VendingMachineTest {
    public static void main(String[] args) {
        Products[] catalog = Products.values();

        VendingMachine vm = new VendingMachine(catalog, null);

        vm.turnON();
        vm.insertCoin(Coins.TENS);

        vm.chooseProduct(Products.COLA);
        vm.insertCoin(Coins.TENS);
        vm.chooseProduct(Products.BEER);
        vm.insertCoin(Coins.FIVES);
        vm.insertCoin(Coins.SHEKEL);
        vm.chooseProduct(Products.CANDY);
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
