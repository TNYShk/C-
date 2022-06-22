package tcode;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public class MatrixMaze {
    final int[][] maze = {
            {1,0,1,0},
            {1,0,1,0},
            {1,0,1,0},
            {0,0,0,0},
    };


    public boolean exitMaze(Point enter, Point exit){
        List<Point> finalPath = getPath(maze,enter,exit);
        printPath(finalPath);
        return finalPath != null;
    //return true;

    }

    public void printPath(List<Point> paths){
        if(paths != null) {
            for (Point p : paths)
                p.getPoint();
        }
    }

    class Point{
        private int row;
        private int col;

        public Point(int row, int col){
            this.row = row;
            this.col = col;
        }
        public void getPoint(){
            System.out.println("r:" + row + " col: "+ col);
        }

    }


    public List<Point> getPath(int[][]maze, Point start, Point exit){
        ArrayList<Point> path = new ArrayList<>();
        HashSet<Point> failedPoints = new HashSet<>();
        if(getPath(maze,exit.row, exit.col, path, failedPoints,start)){
            return path;
        }
        return null;
    }
    private boolean getPath(int[][]maze, int row, int col, List<Point> path, HashSet<Point> fails,Point start){
        if(col<0 || row< 0 || row>3 || col>3|| maze[row][col] ==1)
            return false;

        Point p = new Point(row,col);

        if(fails.contains(p))
            return false;

        boolean isAtStart = (row ==start.row) && (col == start.col);
        if(isAtStart || getPath(maze,row,col-1,path,fails,start) ||
                        getPath(maze,row+1,col-1,path,fails,start) ||
                        getPath(maze,row-1,col,path,fails,start)
                 ){
            path.add(p);
            return true;
        }
        fails.add(p);
        return false;
    }



/*

    private void markLocation(boolean[][]map,Point current){
        map[current.row][current.col] = true;
    }

    public List<Point> getPath(Point start, Point exit){
        boolean[][]beenThere = new boolean[maze[0].length][maze.length];
        List<Point> paths = new LinkedList<>();

        if(getPath(start.row,start.col,paths,exit,beenThere)){
            return paths;
        }
       */
/* for(Point i: paths){
            i.getPoint();
        }*//*

       // System.out.println("here");
        return paths;
    }

    private boolean getPath(int row,int col, List<Point> path, Point exit, boolean[][]beenThere){
        if((exit.col == col) && (exit.row == row))
            return true;

        if((col < 0) || (row < 0) || maze[row][col] == 1 || (col == maze.length) || (row == maze[0].length-1) || beenThere[row][col]){
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
*/

    public static void main(String[] args){
        MatrixMaze test = new MatrixMaze();
        Point start = test.new Point(0,1);
        Point end = test.new Point(2,3);

        System.out.print(test.exitMaze(start,end));
        //System.out.println(test.exitMaze(start,end));
    }
}
