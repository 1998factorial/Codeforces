#include <bits/stdc++.h>
#define INF 18889465931478580854784.0
#define ID if(0)
using namespace std;
typedef long long ll;
typedef long double ld;
ld factorial[55] , ncycle[55] , DP[55];
ll K;
int N;

void init(){
    factorial[0] = 1;
    for(int i = 1; i <= 50; ++i){
        if(factorial[i - 1] >= INF){
            factorial[i] = INF;
        }
        else{
            factorial[i] = factorial[i - 1] * i;
            if(factorial[i] > INF)factorial[i] = INF;
        }
    }
    ncycle[0] = ncycle[1] = 1;
    for(int i = 2; i <= 50; ++i){
        ncycle[i] = factorial[i - 2];
    }
    DP[0] = 1;
    for(int i = 1; i <= 50; ++i){
        for(int j = 1; j <= i; ++j){
            if(ncycle[j] >= INF || DP[i - j] >= INF){
                DP[i] = INF;
            } 
            else{
                DP[i] += ncycle[j] * DP[i - j];
                if(DP[i] >= INF)DP[i] = INF;
            }
        }
    }
}

int find(vector<int>& fa , int x){
    return x == fa[x] ? x : fa[x] = find(fa , fa[x]);
}

void merge(vector<int>& fa , int x , int y){
    x = find(fa , x);
    y = find(fa , y);
    fa[x] = y;
}

// case : 5 21
// exp : 5 3 4 1 2 
// out : 5 4 1 3 2 

int main(){
    init();
    int t;
    cin >> t;
    while(t--){
        cin >> N >> K;
        vector<int> ans(N + 1) , used(N + 1);
        int ok = 1 , csum = 0;
        // csum is the sum of cycle lengths
        for(int i = 1; i <= N && ok; ){
            int found = 0;
            for(int j = 1; j <= N; ++j){
                //cout << "i = " << i << " j = " << j << endl;
                if(used[j])continue;
                ID printf("try %d at %d\n" , j , i);
                int clen = j - csum , nleft = N - csum - clen;
                assert(clen >= 0);
                assert(nleft >= 0);
                ld nways = ncycle[clen] * DP[nleft];
                ID cout << "nawys = " << nways << " K = " << K << endl;
                if(nways >= INF)nways = INF;
                if(nways >= K){
                    //printf("place %d at %d\n" , j , i);
                    // this chunck starts with j
                    used[j] = 1;
                    ans[i] = j;
                    found = 1;
                    vector<int> fa(N + 1);
                    for(int x = 1; x <= N; ++x)fa[x] = x;
                    for(int k = 1; k < clen; ++k){
                        int pos = i + k;
                        int found2 = 0;
                        // now we try to fill digits greedily in this block
                        for(int d = csum + 1; d < csum + clen; ++d){
                            // try d at pos
                            if(used[d])continue;
                            if(d == pos)continue;
                            if(find(fa , d) == find(fa , pos))continue;
                            ID printf("try d = %d at pos = %d\n" , d , pos);
                            ld ways = DP[nleft] * ncycle[clen - k];
                            ID cout << "clen - k = " << clen - k << endl;
                            ID cout << "ways = " << ways << " K = " << K << endl; 
                            assert(clen - k >= 0);
                            if(ways >= INF)ways = INF;
                            if(ways >= K){
                                used[d] = 1;
                                ans[pos] = d;
                                found2 = 1;
                                merge(fa , d , pos);
                                break;
                            }
                            else{
                                K -= ways;
                            }
                        }
                        if(!found2)ok = 0;
                    }
                    csum += clen;
                    i = csum + 1;
                    break;
                }
                else{
                    K -= nways;
                }
            }
            if(!found)ok = 0;
        }

        if(ok && K <= 1)for(int i = 1; i <= N; ++i){
            printf("%d " , ans[i]);
        }
        else printf("-1");
        printf("\n");
    }
}