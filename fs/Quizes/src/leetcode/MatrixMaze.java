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
    //static boolean[][]beenThere = new boolean[maze[0].length][maze.length];

    public boolean exitMaze(Point enter, Point exit){
        List<Point> finalPath = getPath(enter,exit);

        System.out.println(finalPath);
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

    private void markLocation(boolean[][]map,Point current){
        map[current.row][current.col] = true;
    }

    public List<Point> getPath(Point start, Point exit){
        boolean[][]beenThere = new boolean[maze[0].length][maze.length];
        List<Point> paths = new LinkedList<>();


        if(getPath(start.row,start.col,paths,exit,beenThere)){
            return paths;
        }
       /* for(Point i: paths){
            i.getPoint();
        }*/
       // System.out.println("here");
        return paths;
    }

    private boolean getPath(int row,int col, List<Point> path, Point exit, boolean[][]beenThere){
        if((exit.col == col) && (exit.row == row))
            return true;

        if((col < 0) || (row < 0) || maze[row][col] == 1 || (col== maze.length) || (row== maze[0].length-1) || beenThere[row][col]){
            System.out.println("false");
            return false;
        }
        Point p = new Point(row,col);
        //path.add(p);
        markLocation(beenThere,p);

        if(getPath(row,col+1,path,exit,beenThere) || getPath(row+1,col,path,exit,beenThere)){
            path.add(p);
            System.out.println("mm");
            return true;
        }
        if(getPath(row,col-1,path,exit,beenThere) || getPath(row-1,col,path,exit,beenThere)){
            System.out.println("mmmm");
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
