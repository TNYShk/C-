package il.co.ilrd.quiz6;



public class SingletonGen<T> {
    private static SingletonGen<?> instance = null;

    private SingletonGen(){}

    public static<T>SingletonGen<T> getInstance(){
        if(instance == null){
            System.out.println("create instance");
                instance = new SingletonGen<>();

            }
        System.out.println("return instance");
        SingletonGen<T> instance1 = (SingletonGen<T>) instance;
        return instance1;
        }

        public static void main(String[] args){
            SingletonGen<Integer> brr = SingletonGen.getInstance();
            SingletonGen<Double> drr = SingletonGen.getInstance();
            SingletonGen<String> dfrr = SingletonGen.getInstance();
        }
    }

