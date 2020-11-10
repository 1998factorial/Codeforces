#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
typedef pair<int , int> ii;
const int maxn = 6005; 
vector<vector<int>> R;
vector<vector<int>> DP;
int N;
int tot;

int count(int l , int r){
    int cnt = 0;
    for(int i : R[l]){
        cnt += i == r;
    }
    return cnt;
}

int solve(int l , int r){
    if(l > r)return 0;
    if(~DP[l][r])return DP[l][r];
    int& ret = DP[l][r];
    ret = 0;
    int f = count(l , r);
    ret = max(ret , f + solve(l + 1 , r));
    for(int m : R[l]){
        if(m >= r)break;
        ret = max(ret , f + solve(l , m) + solve(m + 1 , r));
    }
    ID printf("DP[%d][%d] = %d\n" , l , r , ret);
    return ret;
}

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        scanf("%d" , &N);
        tot = 0;
        vector<int> tmp;
        map<int , int> mp , imp;
        vector<ii> segs;
        for(int i = 1; i <= N; ++i){
            int l , r;
            scanf("%d %d" , &l , &r);
            segs.emplace_back(l , r);
            tmp.push_back(l);
            tmp.push_back(r);
        }
        sort(tmp.begin() , tmp.end());
        for(int i : tmp){
            if(!mp[i]){
                mp[i] = ++tot;
                imp[tot] = i;
            }
        }
        DP = vector<vector<int>> (tot + 1 , vector<int>(tot + 1 , -1));
        R = vector<vector<int>> (tot + 1);
        for(auto& e : segs){
            int l = mp[e.x] , r = mp[e.y];
            R[l].push_back(r);
        }
        for(int i = 1; i <= tot; ++i){
            sort(R[i].begin() , R[i].end());
        }
        printf("%d\n" , solve(1 , tot));
    }
}