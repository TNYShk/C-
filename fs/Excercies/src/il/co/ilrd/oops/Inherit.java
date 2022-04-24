package il.co.ilrd.oops;

class Inherit {
    private int numl;

    protected Inherit(){
        numl = 45;
    }
    public void smile(){
       System.out.println("clas inherit"+ numl);
    }
    public void smile(String ans){
        System.out.println(ans);
    }

    public void read(){
        System.out.println("read Inherit "+ this.getClass() + " "+ numl);
    }
    public void setData(int n){
        numl = n;
    }
    public int getData(){
        System.out.println("get data"+ this.getClass());
        return numl;
    }
}

class Deri extends Inherit{
    int num2;
    Break something = Break.BREAK;
public Deri(){
    super();
    num2 = 15;
}
    @Override
    public void read(){
        System.out.println("read Deri "+ this.getClass() + " "+ num2);
    }

    public void smile(int x){
    while(--x>=0)
        System.out.println(num2 + " "+ x);
    }

    public void product(){
        int num = getData();
        System.out.println("product= " +(num2*num));
    }

public enum Break{
    REAR,
    MED,
    WELLDONE,
    BREAK
    }
}


