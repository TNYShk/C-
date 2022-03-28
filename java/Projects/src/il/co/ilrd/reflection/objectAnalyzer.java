package il.co.ilrd.reflection;

import java.lang.reflect.*;

public class objectAnalyzer {

    public static void printAncestor(Object object) {
        System.out.println(object.getClass().getSuperclass());
    }

    public static int getModifiers(Object object) {
        return object.getClass().getModifiers();
    }

    public static Class<?>[] getInterfaces(Object object) {
        return object.getClass().getInterfaces();
    }

    public static Field[] getClassMembers(Object object) {
        return object.getClass().getDeclaredFields();
    }

    public static void getName(Object object) {
       Method[] methods = Foo.class.getMethods();
       for(Method method : methods){
           System.out.println("Method: " + method.getName());
       }
    }

    public static Object createInstance(Object object) throws NoSuchMethodException,
            SecurityException, InstantiationException, IllegalAccessException,
            IllegalArgumentException, InvocationTargetException {
        Constructor<?> constructor = object.getClass().getConstructor();

        return constructor.newInstance();
    }

    public static void callMethod(Object object, String method) throws NoSuchMethodException,
            SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
        Method methodToCall = object.getClass().getMethod(method);

        methodToCall.invoke(object);
    }




}
