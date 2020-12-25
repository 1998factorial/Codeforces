#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int maxn = 2e5 + 10;
int A , B , N;
ll hp[maxn] , dmg[maxn];

int main(){
    vector<int> id;
    scanf("%d %d %d" , &N , &A , &B);
    for(int i = 1; i <= N; ++i){
        scanf("%lld %lld" , &hp[i] , &dmg[i]);
        id.push_back(i);
    }
    sort(id.begin() , id.end() , [&](int x , int y){
        return hp[x] - dmg[x] > hp[y] - dmg[y];
    });
    B = min(B , N);
    ll sum = 0;
    for(int i = 0; i < N; ++i){
        int x = id[i];
        if(i < B)sum += max(hp[x] , dmg[x]);
        else sum += dmg[x];
    }
    ll ret = max(ret , sum);
    if(B == 0){
        printf("%lld\n" , ret);
        return 0;
    }
    // operation 1 will be used on only one creature
    ll d = 1ll << A;
    for(int i = 0; i < N; ++i){
        int x = id[i];
        ll nsum = sum;
        if(i < B){
            nsum -= max(hp[x] , dmg[x]);
            nsum += max(hp[x] * d , dmg[x]);
        }
        else{
            int y = id[B - 1];
            nsum -= dmg[x];
            nsum -= max(hp[y] , dmg[y]);
            nsum += max(hp[x] * d , dmg[x]);
            nsum += dmg[y];
        }
        ret = max(ret , nsum);
    }
    printf("%lld\n" , ret);
}