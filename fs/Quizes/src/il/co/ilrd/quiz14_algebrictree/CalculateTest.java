package il.co.ilrd.quiz14_algebrictree;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
public class CalculateTest {
    public static void main(String[] args) {



    }
    @Test
    void TestCalc(){
        AlgebricExpressionTree calc = new AlgebricExpressionTree();

		/*
		               +
		          *          -
		      /     2      8    5
		    6   3

		*/

        Node<String> root = new Node<>("+");
        Node<String> node2 = new Node<>("*");
        Node<String> node3 = new Node<>("-");
        Node<String> node4 = new Node<>("/");
        Node<String> node5 = new Node<>("2");
        Node<String> node6 = new Node<>("8");
        Node<String> node7 = new Node<>("5");
        Node<String> node8 = new Node<>("6");
        Node<String> node9 = new Node<>("3");
        root.setLeft(node2);
        root.setRight(node3);
        node2.setLeft(node4);
        node2.setRight(node5);
        node3.setLeft(node6);
        node3.setRight(node7);
        node4.setLeft(node8);
        node4.setRight(node9);

        System.out.println(calc.calculate(root));
        assertEquals(7.0,calc.calculate(root));

        root.setData("*");
        assertEquals(12.0,calc.calculate(root));
        System.out.println(calc.calculate(root));
    }


}
