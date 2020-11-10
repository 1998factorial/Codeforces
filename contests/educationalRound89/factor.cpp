#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1e5;
bool vis[maxn];
vector<int> fact[maxn];
int N;

int main(){
  cin >> N;
  for(int i = 2; i <= N; ++i){
    if(!vis[i]){
      fact[i].push_back(i);
      for(int j = 2 * i; j <= N; j += i){
        vis[j] = true;
        int tmp = j;
        while(tmp % i == 0){
          fact[j].push_back(i);
          tmp /= i;
        }
      }
    }
  }
  for(int i = 2; i <= N; ++i){
    cout << i << " fac : ";
    for(int j : fact[i])cout << j << " ";
    cout << endl;
  }
}
