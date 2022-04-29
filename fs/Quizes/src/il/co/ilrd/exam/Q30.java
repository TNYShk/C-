package il.co.ilrd.exam;

public class Q30<T> {
    T t1;
    static T t = new T();
    class G{
        T t3;
        void foo(){
            System.out.println(t3);
        }
    }
    static class H<J>{
        T t;
        static J j;
        private void foo(T t){
            System.out.println(t);
        }
        public static void foo2(J j){
           // T t;
            this.t = new T();
            System.out.println(j);
        }
    }
    class MyClass<? extends T>{
        public void foo(){
            T t;
            System.out.println("hi", t);
        }
    }
}
