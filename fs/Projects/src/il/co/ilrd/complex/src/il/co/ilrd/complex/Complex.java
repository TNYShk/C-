package il.co.ilrd.complex;


public class Complex implements Comparable<Complex> {
    private double real = 0;
    private double ifake = 0;

    private Complex(double real, double ifake){
        this.real = real;
        this.ifake = ifake;
    }
    public static Complex createReal(double re){
        return new Complex(re,0);
    }
    public static Complex createImaginary(double fake){
        return new Complex(0,fake);
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
    System.out.println("no no no cant divide by zero!!");
    return null;
    }

    public static Complex parse(String complex){
       StringBuffer copy = new StringBuffer(complex);
       int len = copy.length();
       int blank = copy.indexOf(" ");
       int i = copy.indexOf("i");
       int sign = copy.indexOf("+");
      char [] realnput = new char[blank];
      char [] fakeInput = new char[len - blank];

      copy.getChars(0,blank,realnput,0);
      double dReal = Double.parseDouble(String.valueOf(realnput));
      copy.getChars(blank + 2, i, fakeInput,0);
      double dImage = Double.parseDouble(String.valueOf(fakeInput));

      if (-1 == sign){ dImage *= -1;}
        return new Complex(dReal,dImage);
    }

    private Complex conjugate() {
        Complex conj =  new Complex(this.real, -ifake);
        //System.out.println(conj);
        return conj;
    }


    @Override
    public int compareTo(Complex obj){
        Complex temp = (Complex)obj;

       return (int)(Math.pow(this.getValue(),2) - (Math.pow(temp.getValue(),2)));

    }

    @Override
    public boolean equals(Object obj){

       if (obj instanceof Complex) {
           Complex temp = (Complex) obj;
           return ((temp.real == this.real) && (temp.ifake == this.ifake));
       }
       System.out.println("not a complex num object");
       return false;
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
