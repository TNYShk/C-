package il.co.ilrd.singleton;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

public class testSingletons {

    @Test
    void TestLazySafeS() {

        LazySIngleton s1 = LazySIngleton.getInstance();
        LazySIngleton s2 = LazySIngleton.getInstance();
        assertEquals(s1.hashCode(), s2.hashCode());
        assertEquals(s1.toString(), s2.toString());
        assertTrue(LazySIngleton.getInstance().equals(s2.getInstance()));
        assertTrue(s1.getInstance().equals(s2.getInstance()));
    }

    @Test
    void TestDoubleSafeS() {
        LazyDoubleSingleton s1 = LazyDoubleSingleton.getInstance();
        LazyDoubleSingleton s2 = LazyDoubleSingleton.getInstance();
        assertEquals(s1.hashCode(), s2.hashCode());
        assertEquals(s1.toString(), s2.toString());
    }
    @Test
    void TestSafeUnLazy() {
        NonLazySingleton s1 = NonLazySingleton.getInstance();
        NonLazySingleton s2 = NonLazySingleton.getInstance();
        assertEquals(s1.hashCode(), s2.hashCode());
        assertEquals(s1.toString(), s2.toString());
    }

    @Test
    void TestEnumSafe() {
        EnumSingleton s1 = EnumSingleton.getInstance();
        EnumSingleton s2 = EnumSingleton.getInstance();
        assertEquals(s1.hashCode(), s2.hashCode());
        assertEquals(s1.toString(), s2.toString());
    }

    @Test
    void TestUnSafe() {
        NoThreadSafeSingleton s1 = NoThreadSafeSingleton.getInstance();
        NoThreadSafeSingleton s2 = NoThreadSafeSingleton.getInstance();
        assertTrue(s1.equals(s2));
    }

}
