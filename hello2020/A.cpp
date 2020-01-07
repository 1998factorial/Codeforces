#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

string A[100] , B[100];
int N , M , Q;

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i){
    cin >> A[i];
  }
  for(int i = 1; i <= M; ++i){
    cin >> B[i];
  }
  cin >> Q;
  for(int q = 1; q <= Q; ++q){
    int x; cin >> x;
    string ret = A[(x - 1) % N + 1] + B[(x - 1) % M + 1];
    cout << ret << endl;
  }
}
