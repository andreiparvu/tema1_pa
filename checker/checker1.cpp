#include <cstdio>
#include <cstdlib>
#include <vector>
#include <bitset>

using namespace std;

vector<int>master;
vector<int>slave;
bitset<10001> b;

void die(int punctaj, const char *msg) {
  freopen("score.verif", "wt", stdout);
  printf("%d", punctaj);
  fclose(stdout);

  freopen("output.verif", "wt", stdout);
  printf("%s", msg);
  fclose(stdout);

  exit(0);
}

int main() {
  b.reset();
  master.push_back(0);
  slave.push_back(0);

  FILE *input = fopen("date.in", "rt"), *student = fopen("date.out", "rt"),
       *corect = fopen("res.ok", "rt");

  if (student == NULL) {
    die(0, "Nu exista fisier de output");
  }

  int N,m,s;
  fscanf(input,"%d",&N);
  for (int i = 0; i < N; ++i) {
    fscanf(input,"%d %d", &m, &s);
    if (m < s) {
      swap(m,s);
    }
    master.push_back(m);
    slave.push_back(s);
  }

  int sok = 0;
  fscanf(corect,"%d\n",&sok);

  int rez = 0;
  int ret = fscanf(student,"%d",&rez);
  if (ret == 0) {
    die(0, "Fisier de iesire gol");
  }

  if (rez != sok) {
    die(0, "Salariu incorect.");
  }
  N >>= 1;
  for (int i = 0; i < N; ++i) {
    int ret = fscanf(student,"%d %d", &m, &s);
    if (ret != 2) {
      die(2, "Fisier de iesire incomplet");
    }

    if (m < s) {
      die(2,"Idul Stapanului trebuie sa fie mai mare decat"
             "idul Sclavului\n");
    }
    if (b[m] || b[s]) {
      char msg[1024];
      sprintf(msg, "%d %d perechea %d e platita de cel putin doua ori\n",m,s,i);
      die(2, msg);
    }
    b[m] = b[s] = 1;
    rez -= master[m];
    rez -= slave[s];
  }
  if (rez !=0 ) {
    die(2, "Suma sau configuratie incorecta\n");
  }

  die(5, "Raspuns corect!");
  return 0;
}
