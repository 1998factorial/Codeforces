#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// say we apply reset at i, x -= min(x , y) , y -= min(x , y)
// where x and y are prefix sums for a and b
// if we can win at i, => there exists j, such that
// sa[i] - min(sa[j] , sb[j]) < K and sb[i] - min(sa[j] , sb[j]) >= K

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        int N , K;
        scanf("%d %d" , &N , &K);
        vector<ll> a(N + 1) , b(N + 1);
        for(int i = 1; i <= N; ++i){
            scanf("%lld" , &a[i]);
        }
        for(int i = 1; i <= N; ++i){
            scanf("%lld" , &b[i]);
        }
        vector<ll> sa(N + 1) , sb(N + 1) , minv(N + 1);
        for(int i = 1; i <= N; ++i){
            sa[i] = sa[i - 1] + a[i];
            sb[i] = sb[i - 1] + b[i];
            minv[i] = min(sa[i] , sb[i]);
        }
        // we want to win as soon as possible, as if we can win at i, we do not
        // need to wait until i + 1
        // say we win after round i
        int j = 0 , winpos = -1;
        for(int i = 1; i <= N; ++i){
            while(j <= N && sa[i] - minv[j] >= K)++j;
            if(j <= N && sb[i] - minv[j] >= K){
                winpos = i; // we can win at i
                break;
            }
        }
        if(winpos == -1){
            printf("-1\n");
            continue;
        }
        if(j == 0){
            printf("0\n\n");
            continue;
        }
        vector<int> ops;
        ll s1 = 0 , s2 = 0;
        bool ok = 1;
        for(int i = 1; i < j; ++i){
            s1 += a[i];
            s2 += b[i];
            if(s1 + a[i + 1] >= K){
                ll m = min(s1 , s2);
                s1 -= m;
                s2 -= m;
                ops.push_back(i);
                if(s1 + a[i + 1] >= K)ok = 0;
            }
        }   
        ops.push_back(j);
        if(!ok){
            printf("-1\n");
            continue;
        }
        printf("%d\n" , (int)ops.size());
        for(int i : ops)printf("%d " , i);
        printf("\n");
    }
}