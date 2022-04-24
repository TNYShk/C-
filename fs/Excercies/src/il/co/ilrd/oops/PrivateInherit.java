package il.co.ilrd.oops;

public class PrivateInherit {
    public static void main(String[] args){
      /*  Deri d = new Deri();
        d.setData(20);
        d.num2 = 10;
        d.product();*/

        Inherit tanya = new Deri();
        //tanya.setData(260);
         tanya.smile();
        ((Deri)tanya).smile(4);
        tanya.smile("Hello");


        tanya.read();
        System.out.println(tanya.getData());
        System.out.println("\n");

        Deri fanya = new Deri();
        fanya.smile("Dri");
        fanya.smile();
        fanya.smile(2);
        fanya.smile(0);
        fanya.read();
        System.out.println(fanya.something.ordinal());

       /* Inherit Tanya = new Inherit();
        Tanya.setData(tanya.getData());
        Tanya.read();
        System.out.println(Tanya.getData());*/

    }
}
