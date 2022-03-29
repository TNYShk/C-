package il.co.ilrd.complex;


public class ComplexNumber implements Comparable<ComplexNumber> {
    private double real = 0;
    private double ifake = 0;

    private ComplexNumber(double real, double ifake){
        this.real = real;
        this.ifake = ifake;
    }
    public static ComplexNumber createReal(double re){
        return new ComplexNumber(re,0);
    }
    public static ComplexNumber createImaginary(double fake){
        return new ComplexNumber(0,fake);
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
        return (0 == this.ifake);
    }
    public boolean isImaginary() {
        return (0 != this.ifake);
    }

    public ComplexNumber addition(ComplexNumber that){
        double addReal = this.real + that.real;
        double addifake = this.ifake + that.ifake;

        return new ComplexNumber(addReal, addifake);
    }
    public ComplexNumber substract(ComplexNumber that){
        double subReal = this.real - that.real;
        double subifake = this.ifake - that.ifake;

        return new ComplexNumber(subReal, subifake);
    }
    public ComplexNumber multiplyWith(ComplexNumber other){
        double multReal = this.real * other.real - this.ifake * other.ifake;
        double multifake = this.real * other.ifake + this.ifake * other.real;
        return new ComplexNumber(multReal,multifake);
    }

    public ComplexNumber divideBy(ComplexNumber other) {

        if(other.isImaginary() || (other.real != 0)){
            ComplexNumber otherConjugated = other.conjugate();

            otherConjugated = this.multiplyWith(otherConjugated);
            double mana = Math.pow(other.getValue(), 2);
            double newUp = otherConjugated.getReal() / mana;
            double newDown = otherConjugated.getImaginary() / mana;
            return new ComplexNumber(newUp,newDown);
        }
    System.out.println("no no no cant divide by zero!!");
    return null;
    }

    public static ComplexNumber parse(String complex){

        complex.replace(" ", "");
        double dReal = 0;
        double dFake = 0;
        if(!complex.endsWith("i")){
            dReal = Double.parseDouble(complex);
            return new ComplexNumber(dReal,0);
        }
        StringBuilder copy = new StringBuilder(complex);
        int sign = complex.lastIndexOf("+");
        int minus = complex.lastIndexOf("-");

        if((-1 == sign) && (complex.endsWith("i")) ){
            if((-1 == minus) ||(copy.substring(0,minus).length() < 2)){
                dFake = Double.parseDouble(copy.substring(0,copy.length()-1));
                dReal = 0;
            }
            else {
                dReal = Double.parseDouble(copy.substring(0, minus));
                dFake = Double.parseDouble(copy.substring(minus + 1, copy.length() - 1));
                dFake *= -1;
            }
        }
        else if(-1 != sign){
            dReal = Double.parseDouble(copy.substring(0,sign));
            dFake = Double.parseDouble(copy.substring(sign +1,copy.length()-1));
        }
        else {
            dReal = Double.parseDouble(copy.substring(0, minus));
            dFake = Double.parseDouble(copy.substring(minus + 1, copy.length() - 1));
            dFake *= -1;
        }
        return new ComplexNumber(dReal,dFake);
    }


    private ComplexNumber conjugate() {
       return new ComplexNumber(this.real, -ifake);
    }


    @Override
    public int compareTo(ComplexNumber obj){
        double temp = this.getValue() - obj.getValue();
        double delta = 0.001;
        int answer = (Math.abs(temp) <= delta)? 0: 1;
        return answer;

    }

    @Override
    public boolean equals(Object obj){

       if (obj instanceof ComplexNumber) {
           ComplexNumber temp = (ComplexNumber) obj;
           return ((0 == Double.compare(this.real, temp.real)) && (0 == Double.compare(this.ifake,temp.ifake)));
       }
       System.out.println("not a complex num object");
       return false;
    }

    @Override
    public int hashCode() {
        final int res = 5031;
        Double Re = this.real;
        Double Im = this.ifake;
        int result = 31 * res + Re.hashCode();
        result += 31 * res + Im.hashCode();
        return result;
    }

    @Override
    public String toString(){
        if (real == 0) {
            return "(" + ifake + "i )";
        }
        if (ifake == 0){
            return "(" + real + ")";
        }
        if (ifake <  0) {
            return "(" + real + " - " + (-ifake) + "i )";
        }
        return "(" + real + " + " + ifake + "i )";
    }

}

/*
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



    public static Complex parse(String complex){

        complex.trim();

        if(!complex.endsWith("i")){
            double dReal = Double.parseDouble(complex);
            return new Complex(dReal,0);
        }
        StringBuffer copy = new StringBuffer(complex);
        int sign = complex.lastIndexOf("+");
        int minus = complex.lastIndexOf("-");

        if((-1 == sign) && (complex.endsWith("i")) ){
            if((-1 == minus) ||(copy.substring(0,minus).length() < 2)){
                double fakeParse = Double.parseDouble(copy.substring(0,copy.length()-1));
                return new Complex(0,fakeParse);
            }
            double realParse = Double.parseDouble(copy.substring(0,minus));
            double ifakeParse = Double.parseDouble(copy.substring(minus +1,copy.length()-1));
            return new Complex(realParse,-ifakeParse);
        }

        if(-1 != sign){
            double realParse = Double.parseDouble(copy.substring(0,sign));
            double ifakeParse = Double.parseDouble(copy.substring(sign +1,copy.length()-1));

            return new Complex(realParse,ifakeParse);
        }

        double realp = Double.parseDouble(copy.substring(0,minus));
        double fakep = Double.parseDouble(copy.substring(minus +2,copy.length()-1));

        return new Complex(realp,-fakep);
    }
*/