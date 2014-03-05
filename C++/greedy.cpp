#include <cstdio>
#include <queue>

using namespace std;

#define master first
#define slave second

const int NMAX = 500005;

int main() {
  int n;
  pair<int, int> cost[NMAX];

  freopen("date.in", "rt", stdin);
  freopen("date.out", "wt", stdout);

  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &cost[i].master, &cost[i].slave);
  }

  int rez = cost[1].slave + cost[n].master;

  priority_queue<int> heap;

  for (int i = 2; i < n; i += 2) {
    rez += cost[i].master + cost[i + 1].master;

    heap.push(-(cost[i].slave - cost[i].master));
    heap.push(-(cost[i + 1].slave - cost[i + 1].master));

    rez += -heap.top();
    heap.pop();
  }

  printf("%d\n", rez);

  return 0;
}

