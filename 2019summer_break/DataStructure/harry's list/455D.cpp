#include <iostream>
#include <algorithm>
#include <deque>
#include <cmath>
using namespace std;
/*
  sqrt decomp !!!!!
  we will have sqrt(N) blocks
  for each block , we maintain cnt[1e5] , and a deque (easy append and preppend)
  Memory = O(sqrt(N) * N)
  query :
    1 . L and R in same block , brute force -> O(sqrt(N))
    2 . L and R not in same block , in block[L] at most sqrt(N) numbers ,
    in block[R] at most sqrt(N) numbers , at most sqrt(N) blocks between block[L] and
    block[R] -> O(sqrt(N))
  update :
    1 . L and R in same block , O(1)
    2 . L and R not in same block , need to put last number in block[i] to the head of block[i + 1]
    -> O(sqrt(N))
    Overrall -> O(Q * sqrt(N))
*/
const int maxn = 1e5 + 10;
const int maxnb = 350;
int N , a[maxn] , Q;

struct block{
  int cnt[maxn];
  deque<int> nums;
};

struct square_root_decomp{
  block blocks[maxnb];
  int block_size;

  void init(){ // O(N)
    this->block_size = sqrt(N);
    for(int i = 0; i < N; ++i){
      int id = i / block_size;
      blocks[id].cnt[a[i]]++;
      blocks[id].nums.push_back(a[i]);
    }
  }

  void update(int l , int r){ // O(sqrt(N))
    int L = l / block_size , R = r / block_size;
    int lid = l % block_size , rid = r % block_size;
    auto it = blocks[R].nums.begin() + rid;
    int val = *it;
    blocks[R].nums.erase(it);
    blocks[R].cnt[val]--;
    it = blocks[L].nums.begin() + lid;
    blocks[L].nums.insert(it , val);
    blocks[L].cnt[val]++;
    if(L != R){ // not in same block , we need to shift elements , at most O(sqrt(N)) shifts
      for(int i = L; i < R; ++i){
        int v = blocks[i].nums.back();
        blocks[i].nums.pop_back();
        blocks[i].cnt[v]--;
        blocks[i + 1].nums.push_front(v);
        blocks[i + 1].cnt[v]++;
      }
    }
  }

  int query(int l , int r , int k){ // O(sqrt(N))
    int L = l / block_size , R = r / block_size;
    int lid = l % block_size , rid = r % block_size;
    int ret = 0;
    if(L == R){
      for(int i = lid; i <= rid; ++i){
        auto it = blocks[L].nums.begin() + i;
        ret += *it == k;
      }
    }
    else{
      for(auto it = blocks[L].nums.begin() + lid; it != blocks[L].nums.end(); ++it){ // for L
        ret += *it == k;
      }
      for(int i = 0; i <= rid; ++i){
        auto it = blocks[R].nums.begin() + i;
        ret += *it == k;
      }
      for(int i = L + 1; i < R; ++i){
        ret += blocks[i].cnt[k];
      }
    }
    return ret;
  }

} S;


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 0; i < N; ++i){
    cin >> a[i];
  }
  S.init();
  cin >> Q;
  int lastans = 0;
  for(int q = 1; q <= Q; ++q){
    int ty; cin >> ty;
    if(ty == 1){
      int l , r; cin >> l >> r;
      l = (l + lastans - 1) % N;
      r = (r + lastans - 1) % N;
      if(l > r)swap(l , r);
      //update
      S.update(l , r);
    }
    else if(ty == 2){
      int l , r , k; cin >> l >> r >> k;
      l = (l + lastans - 1) % N;
      r = (r + lastans - 1) % N;
      k = (k + lastans - 1) % N + 1;
      if(l > r)swap(l , r);
      //query
      int ret = S.query(l , r , k);
      cout << ret << endl;
      lastans = ret;
    }
  }
}
