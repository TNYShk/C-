package il.co.ilrd.quiz14_algebrictree;



import java.util.HashMap;

public class AlgebricExpressionTree<T> {

    private HashMap<String,Operator> factoryFun = new HashMap<>();
    private OperatorComponent root;
     final Operator add = ((a, b) -> a + b);
     final Operator minus = ((a, b) -> a - b);
    private final Operator multiply = (a, b) -> a * b;
    private final Operator divide = ((a, b) -> a / b);

    public AlgebricExpressionTree () {
        factoryFun.put("+", add);
        factoryFun.put("-", minus);
        factoryFun.put("*", multiply);
        factoryFun.put("/", divide);
    }

    public double calculate(Node<String> root){
        this.root = new OperatorComponent(root);
        return this.root.calculate();
    }
    private interface Calculator {
        public double calculate();
    }

     interface Operator{
        public double operate(double a, double b);
    }
    private class OperatorComponent implements Calculator{
        private Operator oper;
        private Calculator leftChild;
        private Calculator rightChild;

        public OperatorComponent(Node<String> node) {
            oper = factoryFun.get(node.getData());
            if (null != node.getLeft().getLeft()) {
                leftChild = new OperatorComponent(node.getLeft());
            } else {
                leftChild = new operandComponent(node.getLeft());
            }
            if (null != node.getRight().getLeft()) {
                rightChild = new OperatorComponent(node.getRight());
            } else {
                rightChild = new operandComponent(node.getRight());
            }


        }

        @Override
        public double calculate() {
         return oper.operate(leftChild.calculate(), rightChild.calculate());

        }

    }

    private class operandComponent implements Calculator{
        double answer;

        public operandComponent(Node<String> root){
            answer = Double.parseDouble(root.getData());

        }
        @Override
        public double calculate() {
            return answer;
        }

    }



}
