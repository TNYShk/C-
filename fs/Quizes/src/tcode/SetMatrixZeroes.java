package tcode;

import java.util.*;

public class SetMatrixZeroes {

    public void setZeroes(int[][] matrix) {
        Set<Integer> row = new HashSet<>();
        Set<Integer> column = new HashSet<>();

         for(int i = 0; i< matrix.length; ++i){
             for(int j = 0 ; j< matrix[0].length;++j){
                 if(matrix[i][j] == 0){
                     row.add(i);
                     column.add(j);
                 }
             }
         }
        for(int i = 0; i< matrix.length; ++i){
            for(int j = 0 ; j< matrix[0].length;++j) {
            if(row.contains(i) || column.contains(j))
                matrix[i][j] =0;
            }
        }

        printMat(matrix);
    }
    private void zerofyCol(int[][]mat, int where){
        for(int i =0; i<mat.length; ++i){
            mat[i][where] = 0;
        }
    }
    private void zerofyRow(int[][]mat, int where){
        for(int i =0; i<mat[0].length; ++i){
            mat[where][i] = 0;
        }
    }
    public static void printMat(int[][]matrix){
        for(int i = 0; i< matrix.length; ++i){
            for(int j = 0 ; j< matrix[0].length;++j) {
                System.out.print(matrix[i][j]);
                if (j == matrix[0].length -1)
                    System.out.println();
            }
        }
        System.out.println();
    }

    public static void main(String[] args){
        int[][]mat = {
                {0,1,2,0},
                {3,4,5,2},
                {1,3,1,5}
        };
        printMat(mat);

        SetMatrixZeroes test = new SetMatrixZeroes();
        test.setZeroes(mat);
    }
}
