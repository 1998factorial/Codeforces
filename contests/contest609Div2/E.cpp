#include <iostream>
using namespace std;
typedef long long ll;
/*
  dynamic tree
*/
const int maxn = 2e5 + 10;
int N;
int position[maxn];
ll sum1[maxn << 2] , sum2[maxn << 2];

void add(ll* bit , int pos , ll val){
  while(pos <= N){
    bit[pos] += val;
    pos += pos & (-pos);
  }
}

ll query(ll* bit , int pos){
  ll ret = 0;
  while(pos){
    ret += bit[pos];
    pos -= pos & (-pos);
  }
  return ret;
}

/*int search(ll* bit , int val){
  int i = 0;
  for(int j = 20; j >= 0; --j){
    if((i | (1 << j)) <= N && bit[i | (1 << j)] <= val){
      val -= bit[i |= (1 << j)];
    }
  }
  return i;
}*/

int search(ll* bit , int val){ // alternative way 
  int l = 1 , r = N , ret = -1;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(query(bit , mid) < val){
      l = mid + 1;
    }
    else{
      ret = mid; r = mid - 1;
    }
  }
  return ret;
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i){
    int p; cin >> p;
    position[p] = i;
  }
  ll cnt = 0;
  for(int i = 1; i <= N; ++i){
    int p = position[i];
    add(sum1 , p , 1);
    cnt += i - query(sum1 , p);
    add(sum2 , p , p);
    ll pos = search(sum1 , i / 2 + 1);
    ll sum = 0;
    ll a = i / 2 , b = i - a - 1;
    sum += pos * a - a * (a + 1) / 2 - query(sum2 , pos - 1);
    sum += (query(sum2 , N) - query(sum2 , pos)) - b * pos - b * (b + 1) / 2;
    cout << cnt + sum << " ";
  }
  cout << endl;
}
