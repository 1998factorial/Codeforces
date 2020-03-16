#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const int maxn = 1e5 + 10;

/*
  Each [l , r] is going to be a convex shape made by the interval
  given a time t , we can query the id of the line of best fit at x = t

  sort the lines by gradient (ascending) first as we want maximal
*/

struct line{
    ll m, b;
    int id;
} lines[maxn];

ll floordiv(ll a, ll b){
    return a / b - (a % b && ((a < 0) ^ (b < 0) ));
}

ll intersect(line a, line b){
    return floordiv (b.b - a.b, a.m - b.m);
}

struct Convex{ // modified convex hull trick
	vector<line> cht;
  // need to handle the case when gradient is the same but y-axis-intersection is smaller
	void insert(line l){
		auto n = cht.size();
		while(
      (n >= 1 &&  l.m == cht[n - 1].m && l.b >= cht[n - 1].b)
		    ||
      (n >= 2 && intersect(cht[n - 1], cht[n - 2]) >= intersect(cht[n - 1], l))){
			cht.pop_back();
			n = cht.size();
		}
		cht.push_back(l);
	}

	ll query(ll x){
		int low = 0, high = (int)cht.size() - 2;
		int ret = (int) cht.size() - 1;
		while(low <= high){
			int mid = low + (high - low) / 2;
			if(intersect(cht[mid], cht[mid + 1]) >= x){
				ret = mid;
				high = mid - 1;
			}
      else{
				low = mid + 1;
			}
		}
		return cht[ret].id;
	}
} tree[maxn << 2];

void insert(int pos , int l , int r , int id , line L){
  if(l > r || pos < l || pos > r)return;
  tree[id].insert(L);
  if(l < r){
    int mid = (l + r) >> 1;
    if(pos <= mid)insert(pos , l , mid , id << 1 , L);
    else insert(pos , mid + 1 , r , id << 1 | 1 , L);
  }
}

int query(int l , int r , int x , int y , int id , int time){
  if(l > r || r < x || y < l)return 0;
  if(l <= x && y <= r){
    return tree[id].query(time);
  }
  int mid = (x + y) >> 1;
  if(mid < l){
    return query(l , r , mid + 1 , y , id << 1 | 1 , time);
  }
  if(mid >= r){
    return query(l , r , x , mid , id << 1 , time);
  }
  int id1 = query(l , r , x , mid , id << 1 , time);
  int id2 = query(l , r , mid + 1 , y , id << 1 | 1 , time);
  ll y1 = lines[id1].b + (ll)time * lines[id1].m;
  ll y2 = lines[id2].b + (ll)time * lines[id2].m;
  return (y1 > y2) ? id1 : id2;
}

struct building{
  ll a , b , id;
  building(){}
  building(ll x , ll y , ll z) : a(x) , b(y) , id(z){}
  bool operator < (const building& rhs) const {
    if(b == rhs.b)return a < rhs.a;
    return b < rhs.b;
  }
} B[maxn];

int N , Q;

int main(){
  scanf("%d %d" , &N , &Q);
  for(int i = 1; i <= N; ++i){
    scanf("%lld %lld" , &B[i].a , &B[i].b);
    B[i].id = i;
    lines[i].m = B[i].b;
    lines[i].b = B[i].a;
  }
  sort(B + 1 , B + 1 + N);
  for(int i = 1; i <= N; ++i){
    insert(B[i].id , 1 , N , 1 , {B[i].b , B[i].a , (int)B[i].id});
  }
  while(Q--){
    int l , r , t;
    scanf("%d %d %d" , &l , &r , &t);
    printf("%d\n" , query(l , r , 1 , N , 1 , t));
  }
}
