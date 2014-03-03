// Andrei Parvu
#include <cstdio>

const int NMAX = 505;
const int MOD = 40009;

int unit[NMAX][NMAX], mat[NMAX][NMAX];

void mul(int a[][NMAX], int b[][NMAX], int n) {
  int c[NMAX][NMAX] = {{0}};

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

int power(int val, int p) {
  int rez = 1;
  for (; p; p /= 2) {
    if (p % 2 == 1) {
      rez = (rez * val) % MOD;
      p--;
    }
    val = (val * val) % MOD;
  }

  return rez;
}

int fact(int val) {
  int rez = 1;

  for (int i = 1; i <= val; i++) {
    rez = (rez * i) % MOD;
  }

  return rez;
}

int main() {
  int n, k, m1, m2;

  freopen("date.in", "rt", stdin);
  freopen("date.out", "wt", stdout);

  scanf("%d%d%d%d", &n, &m1, &m2, &k);

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

  for (int nn = n; nn; nn /= 2) {
    if (nn % 2 == 1) {
      mul(unit, mat, k);
      nn--;
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

  int rez = power(col, m1), rez2 = power(2, n) - col;
  if (rez2 < 0) {
    rez2 += MOD;
  }
  rez2 = power(rez2, m2);
  rez = (rez * rez2) % MOD;

  int m = m1 + m2;
  int num = (power(fact(m1), MOD - 2) * power(fact(m2), MOD - 2)) % MOD;

  rez = (rez * fact(m)) % MOD;

  printf("%d\n", (rez * num) % MOD);

  fclose(stdin);
  fclose(stdout);

  return 0;
}

