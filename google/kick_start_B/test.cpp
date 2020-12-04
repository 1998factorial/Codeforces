#include <iostream>
#include <time.h>
using namespace std;

const int maxN = 10;

int main(){
  int T = 100;
  srand(time(NULL));
  cout << T << endl;
  for(int t = 1; t <= T; ++t){
    cout << maxN << " " << rand() % maxN + 1 << endl;
    for(int i = 1; i <= maxN; ++i)cout << rand() % 5 + 1 << " ";
    cout << endl;
  }
}
