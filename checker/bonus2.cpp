  #include <cstdio>
#include <cstring>

#include <algorithm>

#define MOD 40009

#define K_MAX 45

int N, M1, M2;
int K;

int A[K_MAX + 1][K_MAX + 1];

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

void mul(int A[K_MAX + 1][K_MAX + 1], int B[K_MAX + 1][K_MAX + 1]) {
    int C[K_MAX + 1][K_MAX + 1];
    memset(C, 0, sizeof(C));

    for (int i = 0; i <= K; ++i) {
        for (int j = 0; j <= K; ++j) {
            for (int k = 0; k <= K; ++k) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }

    memcpy(A, C, sizeof(C));
}

inline void lgPowMat(int A[K_MAX + 1][K_MAX + 1], int p) {
    int R[K_MAX + 1][K_MAX + 1];
    memset(R, 0, sizeof(R));

    for (int i = 0; i <= K; ++i) {
        R[i][i] = 1;
    }

    for (; p; p >>= 1) {
        if (p & 1) {
            mul(R, A);
        }

        mul(A, A);
    }

    memcpy(A, R, sizeof(R));
}

inline int invMod(int n) {
    return lgPow(n, MOD - 2);
}

inline int comb(int n, int k) {
    int nk = n - k;

    if (k > nk) {
        std::swap(k, nk);
    }

    int p = 1;
    for (int i = 1; i <= k; ++i) {
        p = (p * i) % MOD;
    }
    int r = invMod(p);

    p = 1;
    for (int i = nk + 1; i <= n; ++i) {
        p = (p * i) % MOD;
    }
    r = (r * p) % MOD;

    return r;
}

int main() {
    freopen("date.in", "rt", stdin);
    freopen("date.out", "wt", stdout);

    scanf("%d%d%d%d", &N, &M1, &M2, &K);

    int countCol;
    if (K != 0) {
        memset(A, 0, sizeof(A));
        for (int j = 0; j <= K; ++j) {
            A[0][j] = 1;
        }
        for (int i = 1; i <= K; ++i) {
            A[i][i - 1] = 1;
        }

        lgPowMat(A, N - 1);

        countCol = 0;
        for (int i = 0; i <= K; ++i) {
            countCol += A[i][0] + A[i][1];
        }
        countCol %= MOD;
    } else {
        countCol = 1;
    }

    int countColOther = lgPow(2, N) - countCol;
    if (countColOther < 0) {
        countColOther += MOD;
    }

    printf("%d\n", (((lgPow(countCol, M1) * lgPow(countColOther, M2)) % MOD) * comb(M1 + M2, M1)) % MOD);

    return 0;
}