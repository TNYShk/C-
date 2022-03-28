package il.co.ilrd.reflection;
import java.lang.reflect.*;
import java.lang.reflect.InvocationTargetException;

public class analyzerTest {
    public static void main (String []args)
        throws NoSuchMethodException, SecurityException,
                InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {

        Foo t = new Foo(26);
        objectAnalyzer.printAncestor(t);

        int modifier = objectAnalyzer.getModifiers(t);
        System.out.println("Foo's Modifier: " + Modifier.toString(modifier));

        System.out.println("Foo's interface: "+ objectAnalyzer.getInterfaces(t)[0]);

        System.out.println("Foo's Members:");
        for(Field field : objectAnalyzer.getClassMembers(t)) {
            System.out.println(field);
        }
        System.out.println("calling Foo's Method");
        objectAnalyzer.callMethod(t, "PrintMe" );

        System.out.println("creating instance of Foo via reflection");
        Object s = objectAnalyzer.createInstance(t);
        objectAnalyzer.callMethod(s, "PrintMe" );

    }
}
