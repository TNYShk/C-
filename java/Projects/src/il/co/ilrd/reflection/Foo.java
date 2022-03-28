package il.co.ilrd.reflection;

public class Foo extends Ancestor implements Tanya {
    private int barf = 9;

    public Foo(int x){
        barf = x;
    }
    public Foo(){
        barf = 6;
    }

    private void setBarf(int barf){
        this.barf = barf;
    }

    public int getBarf(){
        return barf;
    }

    @Override
    public void PrintMe() {
        System.out.println("bday barf is " + getBarf());
    }

}

