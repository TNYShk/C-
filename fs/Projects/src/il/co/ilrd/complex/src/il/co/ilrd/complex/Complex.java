package il.co.ilrd.complex;


public class Complex implements Comparable<Complex> {
    private double real = 0;
    private double fake = 0;

    public Complex(double real, double fake){
        this.real = real;
        this.fake = fake;
    }

    public Complex(){
        this(0,0);
    }
    public double getReal() {
        return this.real;
    }
    public double getImaginary() {
        return this.fake;
    }
    public void setReal(double real) {
        this.real = real;
    }
    public void setImaginary(double imaginary) {
        this.fake = imaginary;
    }
    public double getValue(){
        return Math.hypot(real,fake);
    }

    public boolean isReal() {
        return (0 != this.real);
    }
    public boolean isImaginary() {
        return (0 != this.fake);
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

        if(other.isImaginary() || other.isReal()){
            Complex otherConjugated = other.conjugate();

            otherConjugated = this.multiplyWith(otherConjugated);
            double mana = Math.pow(other.getSize(), 2);
            double newUp = otherConjugated.getReal() / mana;
            double newDown = otherConjugated.getImaginary() / mana;
            return new Complex(newUp,newDown);
        }

    return new Complex(666,666);
    }

    private double getSize() {
        return Math.sqrt(Math.pow(this.real, 2) + Math.pow(this.fake, 2));
    }
    public static Complex parse(String complex){
        return new Complex(666,666);
    }
    private Complex conjugate() {
        Complex conj=  new Complex(this.real, -fake);
    System.out.println(conj);
        return conj;
    }


    @Override
    public int compareTo(Complex obj){

        return 1;
    }

    @Override
    public boolean equals(Object obj){
    Complex temp = (Complex)obj;
    return ((temp.real == this.real) && (temp.fake == this.fake));

        return true;
    }

    @Override
    public int hashCode(){
        return 1;
    }





    @Override
    public String toString(){
        if (real == 0) {
            return "( 0 +" + fake + "i";
        }
        if (fake == 0){
            return "(" + real + " + 0.0i";
        }
        if (fake <  0) {
            return "(" + real + " - " + (-fake) + "i)";
        }
        return "(" + real + " + " + fake + "i)";
    }

}
