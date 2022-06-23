package il.co.ilrd.quiz_nonrepeatsequence;

public class FirstNonDuplicate {
    private UniqDLLL Uoutput = new UniqDLLL();

    public void input(long N){
        Uoutput.addNode(N);
    }

    public long output(){
        if (Uoutput.head == null)
                return 0;
        return Uoutput.head.data;
    }

    protected class UniqDLLL {
        Node head, tail = null;
        class Node {
            long data;
            Node next;
            Node prev;

            public Node(long d) {
                data = d;
            }
        }



        private void addNode(long data) {
            Node newby = new Node(data);

            if (head == null) {
                head = tail = newby;
                head.prev = null;
                tail.next = null;
            } else {
                tail.next = newby;
                newby.prev = tail;
                tail = newby;
                tail.next = null;
            }
        }
    }
}
