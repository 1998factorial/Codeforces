#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define x first 
#define y second
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const int MOD = 1e9 + 7;
int N , K , t[305] , a[305];
int cnt[305][305];
int main(){
    scanf("%d %d" , &N , &K);
    rep(i , 1 , N)scanf("%d" , &t[i]) , a[i] = i;
    ll ret = 0;
    do{
        multiset<int> vs;
        int i = 1;
        while(vs.size() < K){
            vs.insert(t[a[i]]);
            ++i;
        }
        int val = 0;
        rep(j , i , N){
            auto it = vs.begin();
            val += *it;
            ret += val;
            vs.erase(vs.find(*it));
            vs.insert(t[a[j]]);
        }
        while(vs.size()){
            auto it = vs.begin();
            val += *it;
            ret += val;
            vs.erase(vs.find(*it));
        }
    }while(next_permutation(a + 1 , a + 1 + N));
    printf("%lld\n" , ret);
}