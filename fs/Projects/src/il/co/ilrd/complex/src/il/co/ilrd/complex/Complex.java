package il.co.ilrd.complex;


public class Complex implements Comparable<Complex> {
    private double real = 0;
    private double ifake = 0;

    public Complex(double real, double ifake){
        this.real = real;
        this.ifake = ifake;
    }

    public Complex(){
        this(0,0);
    }
    public double getReal() {
        return this.real;
    }
    public double getImaginary() {
        return this.ifake;
    }
    public void setReal(double real) {
        this.real = real;
    }
    public void setImaginary(double imaginary) {
        this.ifake = imaginary;
    }
    public double getValue(){
        return Math.hypot(real,ifake);
    }

    public boolean isReal() {
        return (0 != this.real);
    }
    public boolean isImaginary() {
        return (0 != this.ifake);
    }

    public Complex addition(Complex that){
        double addReal = this.real + that.real;
        double addifake = this.ifake + that.ifake;

        return new Complex(addReal, addifake);
    }
    public Complex substract(Complex that){
        double subReal = this.real - that.real;
        double subifake = this.ifake - that.ifake;

        return new Complex(subReal, subifake);
    }
    public Complex multiplyWith(Complex other){
        double multReal = this.real * other.real - this.ifake * other.ifake;
        double multifake = this.real * other.ifake + this.ifake * other.real;
        return new Complex(multReal,multifake);
    }

    public Complex divideBy(Complex other) {

        if(other.isImaginary() || other.isReal()){
            Complex otherConjugated = other.conjugate();

            otherConjugated = this.multiplyWith(otherConjugated);
            double mana = Math.pow(other.getValue(), 2);
            double newUp = otherConjugated.getReal() / mana;
            double newDown = otherConjugated.getImaginary() / mana;
            return new Complex(newUp,newDown);
        }
    System.out.println("cant divide by zero!!\n");
    return null;
    }

    public static Complex parse(String complex){
       StringBuffer copy = new StringBuffer(complex);
       int len = copy.length();
       int blank = copy.indexOf(" ");
       int i = copy.indexOf("i");
       int sign = copy.indexOf("+");
      char [] reali = new char[blank];
      char [] fakei = new char[len - blank];

      copy.getChars(0,blank,reali,0);
      double dreal = Double.parseDouble(String.valueOf(reali));
      copy.getChars(blank + 2, i, fakei,0);
      double dImage = Double.parseDouble(String.valueOf(fakei));

      if (-1 == sign){ dImage *= -1;}
        return new Complex(dreal,dImage);
    }
    private Complex conjugate() {
        Complex conj=  new Complex(this.real, -ifake);
    System.out.println(conj);
        return conj;
    }


    @Override
    public int compareTo(Complex obj){
        Complex temp = (Complex)obj;

        return (int)(Math.pow(this.getValue(),2) - (Math.pow(temp.getValue(),2)));

    }

    @Override
    public boolean equals(Object obj){
    Complex temp = (Complex)obj;
    return ((temp.real == this.real) && (temp.ifake == this.ifake));

    }

    @Override
    public int hashCode(){
        long v = Double.doubleToLongBits(this.getReal());
        long z = Double.doubleToLongBits(this.getImaginary());
        if(z != 0){
            return (int)(v^(z>>32));
        }
        return (int)(z^(v>>32));

    }


    @Override
    public String toString(){
        if (real == 0) {
            return "( 0 " + ifake + "i )";
        }
        if (ifake == 0){
            return "(" + real + " + 0*i )";
        }
        if (ifake <  0) {
            return "(" + real + " - " + (-ifake) + "i )";
        }
        return "(" + real + " + " + ifake + "i )";
    }

}
