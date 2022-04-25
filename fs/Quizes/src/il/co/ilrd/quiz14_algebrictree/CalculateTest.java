package il.co.ilrd.quiz14_algebrictree;

public class CalculateTest {
    public static void main(String[] args) {

        AlgebricExpressionTree calc = new AlgebricExpressionTree();



		/*
		               +
		          *          -
		      /     2      8    5
		    6   3
		 expected result = 12
		*/

        Node<String> node1 = new Node<>("+");
        Node<String> node2 = new Node<>("*");
        Node<String> node3 = new Node<>("-");
        Node<String> node4 = new Node<>("/");
        Node<String> node5 = new Node<>("2");
        Node<String> node6 = new Node<>("8");
        Node<String> node7 = new Node<>("5");
        Node<String> node8 = new Node<>("6");
        Node<String> node9 = new Node<>("3");
        node1.setLeft(node2);
        node1.setRight(node3);
        node2.setLeft(node4);
        node2.setRight(node5);
        node3.setLeft(node6);
        node3.setRight(node7);
        node4.setLeft(node8);
        node4.setRight(node9);

        System.out.println(calc.calculate(node1));
    }


}
