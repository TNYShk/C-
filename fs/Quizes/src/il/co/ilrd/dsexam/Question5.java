package il.co.ilrd.dsexam;
//sea of zeroes
public class Question5 {
    private int lines;
    private int rows;
    static int islands = 0;
    static boolean [][] beenThere;

    public Question5(int row, int line){
        lines = line;
        rows = row;
        beenThere = new boolean[lines][rows];
    }

    public void numOfIslands(int[][]grid){
        islands = 0;
        beenThere = new boolean[lines][rows];
        for(int i =0; i<rows; ++i){
            for(int j =0; j<lines; ++j){
                if(grid[i][j]== 1 && !beenThere[i][j]){
                    islands++;
                    checkAround(grid,i,j);
                }
            }
        }
    }

    private void checkAround(int[][]grid, int i, int j){
        if(i<0 || j<0 || i >= rows || j >= lines || beenThere[i][j] || grid[i][j]==0){
            return;
        }

            beenThere[i][j] = true;


        checkAround(grid, i+1,j);
        checkAround(grid, i+1,j+1);
        checkAround(grid, i,j+1);
        checkAround(grid, i-1,j);
        checkAround(grid, i,j-1);
        checkAround(grid, i-1,j-1);
    }

    public static void main(String[] args){
        int[][] grid = {
                {1,0,0,0},
                {0,1,0,0},
                {0,0,1,0},
                {0,0,0,1},
        };
        Question5 test = new Question5(grid[0].length,grid.length);
        test.numOfIslands(grid);
        System.out.println("num of islands: "+ islands);
    }
}
