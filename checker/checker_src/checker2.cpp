#include <cstdio>
#include <cstdlib>
#include <set>
#include <vector>

using namespace std;

#define ZERO 0
#define TOTAL 5

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
  FILE *student = fopen("date.out", "rt"),
       *corect = fopen("res.ok", "rt");

  if (student == NULL) {
    die(0, "Nu exista fisier de output");
  }

  int raspuns_student, raspuns_corect;
  int ret = fscanf(student, "%d", &raspuns_student);
  if (ret == 0) {
    die(ZERO, "Fisier de iesire gol");
  }
  fscanf(corect, "%d", &raspuns_corect);

  if (raspuns_corect != raspuns_student) {
    die(ZERO, "Raspuns gresit!");
  } else {
    die(TOTAL, "Corect!");
  }

  return 0;
}
