package il.co.ilrd.generics;


import org.testng.annotations.Test;

import static org.testng.Assert.assertTrue;
import static org.testng.AssertJUnit.assertFalse;

public class RecursiveTypeBound {

    public static void main(String[] args){

    }
/*
    if:
    class Fruit<T> implements Comparable<T> -> wont compile, cannot resolve method T 'getSize() in T.
    the getSize() method of T is unknown to the compiler! because the type parameter T of Fruit class doesnt have any bound,
    so T could be any class! (the implements comparable..), its not possible that every lass would've a getSize() method.
    so compiler is right to by angry, and not recognize the getSize() method of T.
 */

    /*
        In generics, when a reference type has a type parameter that is bounded by the reference type itself,
        then that type parameter is said to have a recursive type bound.
        here, the generic type Fruit<T extends Fruit<T>>, Fruit is our reference type,
        its type parameter T is bounded by the Fruit itself, so, the type parameter T has a recursive type bound Fruit<T>.

        A recursive type is one that includes a function that uses that type itself as a type for some argument or its return value.
        here, compareTo(T other) is the function of the recursive type that takes the same recursive type as an argument.
     */


    class Fruit<T extends Fruit<T>> implements Comparable<T>{
        private final Integer size;

        public Fruit(Integer size) {
            this.size = size;
        }

        public Integer getSize(){
            return size;
        }
        @Override
        public int compareTo(T other) {
            return size.compareTo(other.getSize());
        }
    }

    class Apple extends Fruit<Apple>{

        public Apple(Integer size) {
            super(size);
        }
    }

    class Orange extends Fruit<Orange>{

        public Orange(Integer size) {
            super(size);
        }
    }
    class Strawberry extends Fruit<Strawberry>{

        public Strawberry(Integer size) {
            super(size);
        }
    }

    @Test
    void fruitTest(){
        Apple smith = new Apple(3);
        Apple red = new Apple(4);
        assertFalse(smith.compareTo(red) == 0);
        Orange bloodOrange = new Orange(4);
        assertTrue(bloodOrange.getSize().equals(red.getSize()));
        //bloodOrange.compareTo(red);
        Strawberry yam = new Strawberry(2);
        Strawberry yamyam = new Strawberry(2);
        Strawberry num = new Strawberry(2);
        Fruit Straberry = new Fruit<Strawberry>(2);
       System.out.println( Straberry.compareTo(yam));

    }

        


}
