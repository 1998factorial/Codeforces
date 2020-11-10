/*
    constructive , rating 2200
    the goal is to find an invariant
    firstly , we notice that through out the whole process ,
    the sum of C[i] - C[i + 1] will always be C[1] - C[N].
    but this is not strong enough , investigate a bit further ,
    if we let d[i] = C[i] - C[i + 1] , we find that once we
    apply a change on C[i] , we are swapping d[i] and d[i + 1]
    there we have an stronger invariant , we need to make sure that
    number of each d[i] in s is the same as in t
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
int N;
ll c[maxn] , t[maxn];
unordered_map<ll , int> cnt1 , cnt2;

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &c[i]);
    }
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &t[i]);
    }
    if(c[1] != t[1] || c[N] != t[N]){
        printf("No\n");
        return 0;
    }
    for(int i = 1; i < N; ++i){
        ++cnt1[c[i] - c[i + 1]];
        ++cnt2[t[i] - t[i + 1]];
    }
    bool ok = 1;
    for(auto& e : cnt1){
        if(cnt2[e.first] != e.second){
            ok = 0;
        }
    }
    if(ok){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
}
