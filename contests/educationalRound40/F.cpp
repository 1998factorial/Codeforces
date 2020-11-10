#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

/*
  My old Matrix template got TLE :(((
  Can solve this problem with simple dp if M is small
  Since M is very large (<= 1e18)
  we should try matrix
  when there is no obstacle, it is easy to get the matrix
  when there is obstacle on some rows, the whole rows in matrix
  should be set to 0 (view matrix as a directed graph , the edges are
  now gone)
  with this in mind, we can turn this problem into a sweeping + matrix qpow
  problem
  there are 8 possible matrix, so one good way is to store them all and
  write a function to compute which matrix to use given the current
  situation of the rows :)
*/


struct Matrix
{
    static const int maxn = 105;
    ll A[maxn][maxn];
    int len;
    Matrix(){
        memset(A,0,sizeof(A));
        len = 3;
    }
    Matrix(int lens):len(lens){
        memset(A,0,sizeof(A));
    }
    void einit() {
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
                A[i][j] = (i==j);
    }
    void Creat(int lens)
    {
        len = lens;
        if(len > maxn) exit(1);
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
            scanf("%lld",&A[i][j]);
    }
    void output()
    {
        for(int i=0;i<len;i++)
        {
            for(int j=0;j<len-1;j++)
                printf("%lld ",A[i][j]);
            printf("%lld\n",A[i][len-1]);
        }
    }
    Matrix operator * (const Matrix &a){
        Matrix ans(len);
        for(int k=0;k<len;k++)
        {
            for(int i=0;i<len;i++) if(A[i][k])
            {
                ll temp;
                for(int j=0;j<len;j++) if(a.A[k][j])
                {
                    temp = (A[i][k]*a.A[k][j]) % mod;
                    ans.A[i][j] = (ans.A[i][j] + temp) % mod;
                }
            }
        }
        return ans;
    }
    Matrix operator ^ (const ll &b) const { /// 注意运算符号顺序
        Matrix ans(len),a = (*this);ans.einit();
        ll t = b;
        while(t) {
            if(t & 1) ans = ans * a;
            a = a * a;
            t >>= 1;
        }
        return ans;
    }
    void operator = (const Matrix &a){
        len = a.len;
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
            A[i][j] = a.A[i][j];
    }
};
Matrix ret(3), B[8];


int N;
ll M;
const int maxn = 1e4 + 10;

struct event{
  ll row , col , bad;
  event(){}
  event(ll x , ll y , ll z) : row(x) , col(y) , bad(z) {}
  bool operator < (const event& rhs) const {
    return col < rhs.col;
  }
};

vector<event> eve;

ll cnt[3]; // count number of obstacles at row[i]

int cal(){
  int ret = 0;
  for(int i = 0; i < 3; ++i)
    ret |= ((cnt[i] == 0) << i);
  return ret;
}

void show(){
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      cout << ret.A[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void preprocess(){
  for(int i = 0; i < 8; ++i){
    if(i & (1 << 0)){
      B[i].A[0][0] = B[i].A[0][1] = 1;
    }
    if(i & (1 << 1)){
      B[i].A[1][0] = B[i].A[1][1] = B[i].A[1][2] = 1;
    }
    if(i & (1 << 2)){
      B[i].A[2][1] = B[i].A[2][2] = 1;
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= N; ++i){
    ll a , l , r;
    cin >> a >> l >> r;
    eve.emplace_back(a - 1 , l , 1);
    eve.emplace_back(a - 1 , r + 1 , -1);
  }
  sort(eve.begin() , eve.end());
  preprocess();
  ll pre_col = 1;
  ret.A[1][1] = 1;
  for(int i = 0; i < 3; ++i)cnt[i] = 0;
  for(int i = 0; i < eve.size(); ++i){
    ll cur_col = eve[i].col;
    if(cur_col > pre_col){
      ret = ret * (B[cal()] ^ (cur_col - pre_col));
    }
    pre_col = cur_col;
    cnt[eve[i].row] += eve[i].bad;
  }
  ret = ret * (B[7] ^ (M - pre_col));
  cout << (ret.A[1][1] + mod) % mod << endl;
}
