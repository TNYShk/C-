package il.co.ilrd.complex;


public class Complex implements Comparable<Complex> {
    private double real;
    private double fake;

    public Complex(double real, double fake){
        this.real = real;
        this.fake = fake;
    }

    public double getValue(){
        return Math.hypot(real,fake);
    }

    public Complex addition(Complex that){
        double addReal = this.real + that.real;
        double addFake = this.fake + that.fake;

        return new Complex(addReal, addFake);
    }
    public Complex substract(Complex that){
        double subReal = this.real - that.real;
        double subFake = this.fake - that.fake;

        return new Complex(subReal, subFake);
    }
    public Complex multiplyWith(Complex other){
        double multReal = this.real * other.real - this.fake * other.fake;
        double multFake = this.real * other.fake + this.fake * other.real;
        return new Complex(multReal,multFake);
    }

    public Complex divideBy(Complex other) {
        return new Complex(0,0);
    }
    public static Complex parse(String complex){
        return new Complex(666,666);
    }



    @Override
    public int compareTo(Complex obj){
        return 1;
    }

    @Override
    public boolean equals(Object obj){
        return true;
    }

    @Override
    public int hashCode(){
        return 1;
    }

    public boolean isReal() {
        return (0 != this.real);
    }
    public boolean isImaginary() {
        return (0 != this.fake);
    }



    @Override
    public String toString(){
        if (real == 0) {
            return real + "";
        }
        if (fake == 0){
            return fake + "i";
        }
        if (fake <  0) {
            return fake + " - " + (-fake) + "i";
        }
        return real + " + " + fake + "i";
    }

}
