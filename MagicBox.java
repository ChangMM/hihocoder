package com.company;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sin = new Scanner(System.in);
        while(sin.hasNext()) {
            int maxN = 0;
            int x = sin.nextInt();
            int y = sin.nextInt();
            int z = sin.nextInt();
            //得到输入的三个数的排序数组
            int[] cmp = sortXYZ(x,y,z);

            //读取要输如的字符串
            sin.nextLine();
            char[] rby = sin.nextLine().toCharArray();
            int[] cnt = new int[3];
            for (int i = 0; i < rby.length; i++) {
                switch (rby[i]) {
                    case 'B' : cnt[0]++; break;
                    case 'Y' : cnt[1]++; break;
                    case 'R' : cnt[2]++; break;
                    default:
                }
                int[] tmp = new int[3];
                for (int k = 0; k < 3; k++) {
                    tmp[k] = cnt[k];
                }
                Arrays.sort(tmp);
                int[] tmp2 = getDiff(tmp);

                boolean flag = true;
                for (int j = 0; j < tmp2.length; j++) {
                    if (tmp2[j] != cmp[j]) {
                        flag = false;
                        break;
                    }
                }
                if (cnt[0] + cnt[1] + cnt[2] > maxN) {
                    maxN = cnt[0] + cnt[1] + cnt[2];
                }
                if (flag) {
                    cnt[0] = 0; cnt[1] = 0; cnt[2] = 0;
                }
            }
            System.out.println(maxN);
        }
    }

    private static int[] getDiff(int[] A) {
        int[] ra = new int[3];
        ra[0] = A[1] - A[0] > A[2] - A[1] ? A[2] - A[1] : A[1] - A[0];
        ra[1] = A[1] - A[0] > A[2] - A[1] ? A[1] - A[0] : A[2] - A[1];
        ra[2] = A[2] - A[0];
        return ra;
    }

    private static int[] sortXYZ(int x, int y, int z) {
        int[] tmpInt = new int[3];
        tmpInt[0] = Math.min(x, Math.min(y, z));
        tmpInt[2] = Math.max(x, Math.max(y, z));
        tmpInt[1] = x + y + z - tmpInt[0] - tmpInt[2];
        return tmpInt;
    }
}