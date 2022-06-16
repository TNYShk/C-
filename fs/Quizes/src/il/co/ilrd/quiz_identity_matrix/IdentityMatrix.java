package quiz_identity_matrix;

public class IdentityMatrix {
    static int[][]matrix2 = {
            {2,3,4,5},
            {6,7,8,9},
            {2,3,1,0},
            {3,3,0,1}
    };
    static int[][]matrix = {
            {2,3,4,5},
            {6,7,8,9},
            {2,3,4,0},
            {3,3,3,1}
    };
    static int[][]matrix1 = {
            {2,3,4,5,6},
            {6,7,8,9,5},
            {2,3,1,0,5},
            {3,3,0,1,0},
            {3,3,0,0,1},
    };


    public int matrixOutput(){
        int length = matrix[0].length;
        int sum = 0;
        for(int i=length-1; i!=0; --i){
            if(matrix[i][i]==1)
                if(checkZero(i))
                    sum+=1;
        }
        return sum;
    }

    private boolean checkZero(int idx){
        if(idx == matrix[0].length-1)
            return matrix[idx-1][idx] == 0;
        return matrix[idx+1][idx] == 0;
    }

    public static void main(String[] args){
        IdentityMatrix test = new IdentityMatrix();
        System.out.println(test.matrixOutput());

    }
}
