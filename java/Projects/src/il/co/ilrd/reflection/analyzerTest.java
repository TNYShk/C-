package il.co.ilrd.reflection;
import java.lang.reflect.*;
import java.lang.reflect.InvocationTargetException;

public class analyzerTest {
    public static void main (String []args)
        throws NoSuchMethodException, SecurityException,
                InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {

        Foo t = new Foo(26);
        System.out.print("Foo's Ancestor: ");
        objectAnalyzer.printAncestor(t);

        int modifier = objectAnalyzer.getModifiers(t);
        System.out.println("Foo class Modifier: " + Modifier.toString(modifier));

        System.out.println("Foo implements: "+ objectAnalyzer.getInterfaces(t)[0]);

        System.out.print("Foo's Members: ");
        for(Field field : objectAnalyzer.getClassMembers(t)) {
            System.out.println(field);
        }
        System.out.println("Foo's Methods:");
        objectAnalyzer.getName(t);


        System.out.println("\ncalling specific Foo Method");
        objectAnalyzer.callMethod(t, "PrintMe" );

        System.out.println("\ncreating instance of Foo via reflection");
        Object s = objectAnalyzer.createInstance(t);
        objectAnalyzer.callMethod(s, "PrintMe" );

        Ancestor.bla();

    }
}
