package il.co.ilrd.inner;

interface Tanya{
   public void accessMembers();
}

public class OuterClass {
    String outerField = "Outer field";
    private String test = "outer class private string";
    static String staticOuterField = "Static outer field";
/*
// can't have static method inside non static class.
    public void foo(){
        class AIC{
            public static void foo2(){}
        }
        AIC.foo2(); // need to instantiate class AIC first!
    }
  */
    public void methodOffer(){
        int x = 7;
        System.out.println("here "+ x);

        class Localy{

            String veryLocal = "outer class- method-inner class";
            void localMethod(){
                System.out.println(veryLocal);
            }
        }
    }

    private class InnerClass {

        void accessMembers() {
            System.out.println();
            System.out.println(outerField);
            System.out.println(staticOuterField);
            System.out.println("inside Inner class");
            methodOffer();

        }

        public void testy() {
            System.out.print("snonymus!");
            InnerClass anonysmus = new InnerClass() {

          /* @Override
           public void accessMembers() {
                System.out.println("anonymus!anonymus!anonymus!anonymus!anonymus!");
            }*/
        };
            anonysmus.accessMembers();
    }

    }

    private static class StaticNestedClass {
        static int yy = 6;
        void accessMembers(OuterClass outer) {
            // Compiler error: Cannot make a static reference to the non-static
            //     field outerField
            // System.out.println(outerField);
            System.out.println(outer.outerField);

            System.out.println(outer.test);
            System.out.println(staticOuterField);


        }
    }

    private static class AnotherNest{

        void accessMem(){
            System.out.print(StaticNestedClass.yy);

        }
    }

    public static void main(String[] args) {
        System.out.println("Inner class:");
        System.out.println("------------");
        OuterClass outerObject = new OuterClass();
        InnerClass innerObject = outerObject.new InnerClass();
        innerObject.accessMembers();
        innerObject.testy();

        System.out.println("\nStatic nested class:");
        System.out.println("--------------------");

        StaticNestedClass staticNestedObject = new StaticNestedClass();
        staticNestedObject.accessMembers(outerObject);

        System.out.println("\nTop-level class:");
        System.out.println("--------------------");
        TopLevel topLevelObject = new TopLevel();
        topLevelObject.accessMembers(outerObject);
        System.out.println("\nData Structure inner class implements interface test:");
        System.out.println("--------------------");
        DataStructure ds = new DataStructure();
        ds.printEven();
    }



}
