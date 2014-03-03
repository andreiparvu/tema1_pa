#include <cstdio>

#define MOD 40009

#define N_MAX 1000010
#define K_MAX 45

int N, M;
int K;

/**
 * a[i][j] = cate siruri (coloane) exista care au lungime i
 * si se termina cu j biti setati
 */
int a[N_MAX][K_MAX];

inline int lgPow(int n, int p) {
    int res = 1;

    for (; p; p >>= 1) {
        if (p & 1) {
            res = (res * n) % MOD;
        }

        n = (n * n) % MOD;
    }

    return res;
}

int main() {
    freopen("date.in", "rt", stdin);
    freopen("date.out", "wt", stdout);

    scanf("%d%d%d", &N, &M, &K);

    a[1][0] = 1;
    a[1][1] = (K == 0 ? 0 : 1);

    for (int i = 2; i <= N; ++i) {
        int sumPrev = 0;

        for (int j = 1; j <= i && j <= K; ++j) {
            sumPrev += a[i - 1][j - 1];
            if (sumPrev >= MOD) {
                sumPrev -= MOD;
            }

            a[i][j] = a[i - 1][j - 1];
        }

        if (i - 1 >= K) {
            sumPrev += a[i - 1][K];
            if (sumPrev >= MOD) {
                sumPrev -= MOD;
            }
        }

        a[i][0] = sumPrev;
    }

    int countCol = 0;
    for (int i = 0; i <= N && i <= K; ++i) {
        countCol += a[N][i];
        if (countCol >= MOD) {
            countCol -= MOD;
        }
    }

    printf("%d\n", lgPow(countCol, M));

    return 0;
}
