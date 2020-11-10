#include <bits/stdc++.h>
#define MAX_SIZE 1048596
#define MID ((l + r) >> 1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;
typedef long long ll;
/* 
    DP[i] = A * DP[i + 1] + B * DP[i + 2]
    
    DP[i]       A B   DP[i + 1]      
    DP[i + 1]   1 0   DP[i + 2]
*/

const ll mod = 998244353;
const int maxn = 5e5 + 10;
int N , M;
char s[maxn];
ll C[100];

ll mul(ll x , ll y){
    return x * y % mod;
}

ll add(ll x , ll y ){
    ll ret = x + y;
    if(ret > mod)ret %= mod;
    return ret;
}

void init(){
    for(int i = 0; i <= 18; ++i){
        for(int a = 0; a <= 9; ++a){
            for(int b = 0; b <= 9; ++b){
                C[i] += (a + b == i);
            }
        }
    }
}

struct Matrix {
    ll a[2][2];
    Matrix operator *(Matrix other) const {
        Matrix mt;
        int i, j, k;
        for (i = 0 ; i < 2; ++i) {
            for (j = 0 ; j < 2; ++j) {
                mt.a[i][j] = 0;
                for (k = 0 ; k < 2; ++k) {
                    mt.a[i][j] = add(mt.a[i][j], mul(a[i][k], other.a[k][j]));
                }
            }
        }
        return mt;
    }    
};
 
Matrix tree[MAX_SIZE];
 
Matrix gen(int pos){
    Matrix ret;
    ret.a[1][0] = 1;
    ret.a[1][1] = 0;
    ret.a[0][0] = C[s[pos] - '0'];
    ret.a[0][1] = 0;
    if(pos != N && s[pos] == '1'){
        ret.a[0][1] = C[(s[pos] - '0') * 10 + (s[pos + 1] - '0')];
    }
    return ret;
}

void update(int pt, int l, int r, int index, Matrix mt) {
    if (l > r || pt < l || pt > r) return;
    if (l == r) {
        tree[index] = mt;
        return;
    }
 
    if (pt <= MID) {
        update(pt, l, MID, LEFT, mt);
    } else {
        update(pt, MID + 1, r, RIGHT, mt);
    }
 
    tree[index] = tree[LEFT] * tree[RIGHT];
}

void build(int l , int r , int index){
    if(l == r){
        tree[index] = gen(l);
    }
    else{
        build(l , MID , LEFT);
        build(MID + 1 , r , RIGHT);
        tree[index] = tree[LEFT] * tree[RIGHT];
    }
}

int main(){
    init();
    scanf("%d %d" , &N , &M);
    scanf("%s" , s + 1);
    build(1 , N , 1);
    while(M--){
        int pos , val; 
        scanf("%d %d" , &pos , &val);
        s[pos] = '0' + val;
        Matrix m = gen(pos);
        update(pos , 1 , N , 1 , m);
        if(pos != 1){
            Matrix mm = gen(pos - 1);
            update(pos - 1 , 1 , N , 1 , mm);
        }
        printf("%lld\n" , tree[1].a[0][0]);
    }
}