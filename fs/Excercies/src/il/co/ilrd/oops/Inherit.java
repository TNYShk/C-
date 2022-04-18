package il.co.ilrd.oops;

class Inherit {
    private int numl;

    public void setData(int n){
        numl = n;
    }
    public int getData(){
        return numl;
    }
}

class Deri extends Inherit{
    int num2;



    public void product(){
        int num = getData();
        System.out.println("product= " +(num2*num));
    }
}


