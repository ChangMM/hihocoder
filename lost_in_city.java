package com.company;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int row = sc.nextInt();
        int column = sc.nextInt();

        char [][]cityMap = new char[row][column];  //获取城市的地图
        for(int i=0;i<row;i++){
            String str = sc.next();
            for(int j=0;j<column;j++){
                cityMap[i][j]= str.charAt(j);
            }
        }

        //获取可能的四种3*3的hi的布局
        char[][] hi1 = new char[3][3];
        char[][] hi2 = new char[3][3];
        char[][] hi3 = new char[3][3];
        char[][] hi4 = new char[3][3];

        for(int i=0;i<3;i++){
            String str = sc.next();
            for(int j=0;j<3;j++){
                char c = str.charAt(j);
                hi1[i][j] = c;
                hi2[2-i][2-j] =c;
                hi3[2-j][i] =c;
                hi4[j][2-i] =c;
            }
        }

        PriorityQueue<Point> queen= new PriorityQueue<>();

        for(int i=1;i<row-1;i++){
            for(int j=1;j<column-1;j++){
                if(isHere(hi1, cityMap, i, j)||isHere(hi2, cityMap, i, j)
                        ||isHere(hi3, cityMap, i, j)||isHere(hi4, cityMap, i, j)){
                    queen.add(new Point(i,j));
                }
            }
        }

        Point p = queen.poll();

        while(p!=null){
            System.out.println((p.x+1)+" "+(p.y+1));
            p = queen.poll();
        }
    }

    private static boolean isHere(char[][] hi, char[][] cityMap, int row, int column) {
        if (hi[1][1] != cityMap[row][column])
            return false;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (hi[i][j] != cityMap[row + i - 1][column + j - 1]) {
                    return false;
                }
            }
        }
        return true;
    }
}

class Point implements Comparable{
    int x, y;
    Point(int x,int y){
        this.x = x;
        this.y = y;
    }

    @Override
    public int compareTo(Object o) {
        Point other = (Point) o;
        if(this.x==other.x){
            return this.y - other.y;
        }
        return this.x - other.x;
    }
}
