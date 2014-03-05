/**
date.in:
6
3 0
7 1
2 0
5 1
6 0
4 2

pt 2N = 6
id: master slave
1: 3 0
2: 7 1
3: 2 0
4: 5 1
5: 6 0
6: 4 2

rez = slave[1] + master [6] = 0 + 4 = 4; (pentru ca altfel nu au cum sa fie grupati)

Pas1: a) iau perechile 2 si 3. Le consider masteri => rez += master[2] + master[3] => 4 + 7 + 2 = 13
         b) bag in set 7-1 si 2-0 si trebuie sa scot un master pentru ca am deja prea multi (3 masters la 1 slave) =>
         scot maximul din set adica 6 si il scad din rez => 13-6 = 7; [acum l-am scos pe 6 din set].
         numarul de masters = numarul de slaves => ok.

Pas2: a) iau perechile 4 5 le fac masters => rez += 5 + 6 => 7 + 5 + 6 = 18;
         b) bag in set 5-1 si 6-0. Setul contine 6, 4, 2. Iau maximul din set si il scot din rez
         => rez = 18 - 6 = 12. Il scot pe 6 din set. numarul de masters = numarul de slaves => ok.

Pas3: nu mai am perechi => toti cei ramasi in set sunt slaves.

Aici problema se poate completa cu: spuneti suma minima si dati o modalitate de grupare:

Pt cuplarea o sa fie ceva de genu:
listaSlaves = [0, 3, 4]
listaMasters = [2, 5, 6];
si se cupleaza listaSlaves[i] cu listaMasters[i].
*/
#include <cstdio>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

multiset <pair<int,int> > multime;
vector<int> mastersM;
vector<int> slavesM;
inline void citestePereche(int &rez, int i) {
  int master,slave;
  scanf("%d%d",&master,&slave);
  //if (master < slave) {
    //swap(master,slave);
  //}
  rez += master; //initial toti sunt masteri
  multime.insert(multime.begin(),make_pair(master-slave, i)); //adaug in set diferenta dintre cele 2 valori
  //pentru a afla o cuplare corecta se va adauga in set o pereche (diferenta,id) si nu se va mai strica N;
}
int main() {
  freopen("date.in","r",stdin);
  freopen("date.out","w",stdout);
  int N;
  int rez = 0;
  scanf("%d",&N);
  slavesM.push_back(1);

  int master, slave;
  scanf("%d%d",&master,&slave);

  rez += slave; // prima pereche sigur este slave

  int i;
  for (i = 2; i < N; ) {
    citestePereche(rez, i);
    ++i;
    citestePereche(rez, i);
    ++i;
    /*
    Pentru ca am mai multi masters decat slaves (masters + 1= slaves)
    transform master-ul cu diferenta maxima din set in slave
    (pentru ca vreau ca rezultatul final sa fie minim)
    */
    multiset<pair<int,int> > :: iterator devineSlave = multime.end();
    --devineSlave;
    rez -= devineSlave -> first;
    slavesM.push_back(devineSlave -> second);
    multime.erase(devineSlave); //masterul care a devenit slave il scot din set
    //daca vreau si cuplarea adaug id-ul curent in lista de slaves
  }
  citestePereche(rez, N);
  printf("%d\n",rez);
  multime.clear();
  sort(slavesM.begin(), slavesM.end());
  int pas = 0;
  for (int i = 1; i <= N; ++i) {
    if ( pas < slavesM.size() && i == slavesM[pas]) {
      //printf("slave %d\n",slavesM[pas]);
      ++pas;
      continue;
    }
    //printf("master %d\n",i);
    mastersM.push_back(i);
  }
  for (int i = 0; i < mastersM.size(); ++i) {
    printf("%d %d\n", mastersM[i], slavesM[i]);
  }
  return 0;
}
