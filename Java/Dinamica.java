// Andrei Parvu

import java.io.IOException;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Dinamica {
  private static final int NMAX = 505;
  private static final int MOD = 40009;

  public static void main(String[] args) {
    int n = 0, k = 0, m = 0;

    try {
      Scanner s = new Scanner(new File("date.in"));
      n = s.nextInt();
      m = s.nextInt();
      k = s.nextInt();
    } catch (IOException ex) {}


    int[][] mat = new int[NMAX][NMAX], unit = new int[NMAX][NMAX];
    // D[i][j] = D[i - 1][j - 1]
    // D[i][0] = D[i - 1][j], oricare j
    for (int i = 0; i <= k; i++) {
      mat[i][0] = 1;
      if (i > 0) {
        mat[i - 1][i] = 1;
      }
    }

    for (int i = 0; i <= k; i++) {
      unit[i][i] = 1;
    }

    for (; n > 0; n /= 2) {
      if (n % 2 == 1) {
        mul(unit, mat, k);
        n--;
      }
      mul(mat, mat, k);
    }

    int col = 0;

    for (int i = 0; i <= k; i++) {
      col += unit[0][i];
      if (col >= MOD) {
        col -= MOD;
      }
    }

    PrintWriter pw = null;
    try {
      pw = new PrintWriter("date.out");
    } catch (FileNotFoundException ex) {}

    pw.println(power(col, m));
    pw.flush();
  }

  private static void mul(int a[][], int b[][], int n) {
    int[][] c = new int[NMAX][NMAX];

    for (int k = 0; k <= n; k++) {
      for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
          c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
        }
      }
    }

    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        a[i][j] = c[i][j];
      }
    }
  }

  private static int power(int val, int p) {
    int rez = 1;
    for (; p > 0; p /= 2) {
      if (p % 2 == 1) {
        rez = (rez * val) % MOD;
        p--;
      }
      val = (val * val) % MOD;
    }

    return rez;
  }

  private static int fact(int val) {
    int rez = 1;

    for (int i = 1; i <= val; i++) {
      rez = (rez * val) % MOD;
    }

    return rez;
  }
}

