#include <iostream>
using namespace std;
typedef long long ll;
/*
  segment tree
*/
const int maxn = 2e5 + 10;
ll sum1[maxn << 2] , sum2[maxn << 2];
int N , pos[maxn] , a[maxn];

void update(ll* tree , int pos , int l , int r , int id , ll val){
  if(l > r || pos < l || pos > r)return;
  if(pos == l && pos == r){
    tree[id] += val;
  }
  else{
    int mid = (l + r) >> 1;
    update(tree , pos , l , mid , id << 1 , val);
    update(tree , pos , mid + 1 , r , id << 1 | 1 , val);
    tree[id] = tree[id << 1] + tree[id << 1 | 1];
  }
}

ll query(ll* tree , int l , int r , int x , int y , int id){
  if(l > r || x > y || x > r || y < l)return 0;
  if(l <= x && y <= r){
    return tree[id];
  }
  int mid = (x + y) >> 1;
  if(mid < l)
    return query(tree , l , r , mid + 1 , y , id << 1 | 1);
  if(mid >= r)
    return query(tree , l , r , x , mid , id << 1);
  return query(tree , l , r , x , mid , id << 1) + query(tree , l , r , mid + 1 , y , id << 1 | 1);
}

int search(ll* tree , ll val){ //find smallest x such that sum1[1 .. x] >= val
  int l = 1 , r = N , ret = -1;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(query(tree , 1 , mid , 1 , N , 1) < val){
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
  for(int i = 1; i <= N; ++i)cin >> a[i] , pos[a[i]] = i;
  ll cnt = 0;
  for(int i = 1; i <= N; ++i){
    int p = pos[i];
    update(sum1 , p , 1 , N , 1 , 1);
    cnt += i - query(sum1 , 1 , p , 1 , N , 1);
    update(sum2 , p , 1 , N , 1 , p);
    ll a = i / 2 , b = i - a - 1, pos = search(sum1 , i / 2 + 1) , sum = 0;
    sum += -query(sum2 , 1 , pos - 1 , 1 , N , 1) + query(sum2 , pos + 1 , N , 1 , N , 1);
    sum += (a * pos - a * (a + 1) / 2) - (b * pos + b * (b + 1) / 2);
    cout << cnt + sum << " ";
  }
  cout << endl;
}
