package com.company;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sin = new Scanner(System.in);
        int maxN = 0;
        while(sin.hasNext()) {
            int m = sin.nextInt(),
                n = sin.nextInt();

            int[] arr = new int[m];
            for(int i = 0;i < m;i++){
                arr[i] = sin.nextInt();
            }
            maxN = getMaxN(arr,n);
            System.out.println(maxN);
        }
        sin.close();
    }

    private static int getMaxN(int[] arr,int n){
        int max = 0,
            len = arr.length;
        if(n >= len){
            max = 100;
        }else{
            int res = arr[n]-1;
            for(int i =0;i+n+1<len;i++){
                res = Math.max(res,arr[i+n+1]-arr[i]-1);
            }
            max = Math.max(res,100-arr[len-n-1]);

        }
        return max;
    }
}
