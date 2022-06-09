package leetcode;

import com.sun.org.apache.xerces.internal.util.SynchronizedSymbolTable;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;

public class MatrixMaze {
    static int[][]maze = {
            {1,0,1,0},
            {1,0,1,0},
            {1,0,1,0},
            {0,0,0,0},
    };
    static boolean[][]beenThere = new boolean[maze[0].length][maze.length];

    public boolean exitMaze(Point enter, Point exit){
        List<Point> finalPath = getPath(enter);

        //System.out.println(finalPath);
    //return true;
   return finalPath.contains(exit);
    }

    class Point{
        private int row;
        private int col;

        public Point(int x, int y){
            this.row = x;
            this.col = y;
        }
        public void getPoint(){
                System.out.println(row+":"+col);
        }
    }

    private void markLocation(Point current){
        beenThere[current.row][current.col] = true;
    }

    public List<Point> getPath(Point start){
       List<Point> path = new LinkedList<>();
        if(maze == null || maze.length == 0)
            return null;


        if(getPath(start.row,start.col,path)){
            return path;
        }
        for(Point i: path){
            i.getPoint();
        }
       // System.out.println("here");
        return path;
    }

    private boolean getPath(int row,int col, List<Point> path){
        if((col < 0) || (row < 0) || maze[row][col] == 1 || (col== maze.length) || (row== maze[0].length-1) || beenThere[row][col]){
            System.out.println("false");
            return false;
        }
        Point p = new Point(row,col);
        //path.add(p);
        markLocation(p);

        if(getPath(row,col+1,path) || getPath(row+1,col,path)){
            path.add(p);
            return true;
        }
        if(getPath(row,col-1,path) || getPath(row-1,col,path)){
            path.add(p);
            return true;
        }

        return true;
    }

    public static void main(String[] args){
        MatrixMaze test = new MatrixMaze();
        Point start = test.new Point(0,1);
        Point end = test.new Point(0,3);

        test.exitMaze(start,end);
        //System.out.println(test.exitMaze(start,end));
    }
}
