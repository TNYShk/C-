package il.co.ilrd.singleton;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

public class testSingletons {

    @Test
    void TestLazySafeS() {
        LazySIngletonSafe s1 = LazySIngletonSafe.getInstance();
        LazySIngletonSafe s2 = LazySIngletonSafe.getInstance();
        assertEquals(s1.hashCode(), s2.hashCode());
        assertEquals(s1.toString(), s2.toString());
        assertTrue(LazySIngletonSafe.getInstance().equals(s2.getInstance()));
        assertTrue(s1.getInstance().equals(s2.getInstance()));
    }


}
