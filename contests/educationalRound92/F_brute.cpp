#include <bits/stdc++.h>
#define x first
#define y second
#define ID if(0)
using namespace std;
const int maxn = 500;
struct seg{
    int l , r , t;
    seg(){}
    seg(int l_ , int r_ , int t_) : l(l_) , r(r_) , t(t_) {}
    bool operator < (const seg& rhs) const {
        return r < rhs.r;
    }
};
seg segs[maxn];
int N;
int tot = 0;
vector<int> tmp;
map<int , int> mp , imp;
int black[500][1000];
int white[500][1000];
int cnt_black[1000][1000];
int cnt_white[1000][1000];

void init(){
    sort(tmp.begin() , tmp.end());
    for(int i : tmp){
        if(!mp[i]){
            mp[i] = ++tot;
            imp[tot] = i;
        }
    }
    ID for(auto& e : mp){
        printf("(%d %d)\n" , e.x , e.y);
    }
}

int solve(){
    int i , j , l , r , ret = 0 , x , y;
    sort(segs + 1 , segs + 1 + N);
    for(i = 1; i <= N; ++i){
        l = mp[segs[i].l] , r = mp[segs[i].r];
        ID printf("inter(%d %d) \n" , l , r);
        for(x = 0; x <= tot; ++x){
            for(y = x; y <= tot; ++y){
                if(x <= l && r <= y){
                    if(segs[i].t == 0)++cnt_white[x][y];
                    else ++cnt_black[x][y];
                }
            }
        }
    }
    ID for(x = 0; x <= tot; ++x){
        for(y = x; y <= tot; ++y){
            printf("cnt_black[%d][%d] = %d\n" , x , y , cnt_black[x][y]);
        }
    }
    ID for(x = 0; x <= tot; ++x){
        for(y = x; y <= tot; ++y){
            printf("cnt_white[%d][%d] = %d\n" , x , y , cnt_white[x][y]);
        }
    }
    memset(black , -1 , sizeof(black));
    memset(white , -1 , sizeof(white));
    black[0][0] = 0;
    white[0][0] = 0;
    for(i = 1; i <= N; ++i){
        l = mp[segs[i].l] , r = mp[segs[i].r];
        for(j = 0; j <= tot; ++j){ // we do not choose segs[i]
            black[i][j] = max(black[i][j] , black[i - 1][j]);
            white[i][j] = max(white[i][j] , white[i - 1][j]);
        }
        if(segs[i].t == 1){
            for(j = 0; j < l; ++j){
                black[i][r] = max(black[i][r] , white[i - 1][j] + cnt_black[j + 1][r]);
            }
        }
        else{
            for(j = 0; j < l; ++j){
                white[i][r] = max(white[i][r] , black[i - 1][j] + cnt_white[j + 1][r]);
            }
        }
    }
    ID for(i = 1; i <= N; ++i){
        for(j = 0; j <= tot; ++j){
            printf("black[%d][%d] = %d\n" , i , j , black[i][j]);
        }
    }
    ID for(i = 1; i <= N; ++i){
        for(j = 0; j <= tot; ++j){
            printf("white[%d][%d] = %d\n" , i , j , white[i][j]);
        }
    }
    for(j = 0; j <= tot; ++j){
        ID printf("black[%d][%d] = %d\n" , N , j , black[N][j]);
        ID printf("white[%d][%d] = %d\n" , N , j , white[N][j]);
        ret = max(ret , black[N][j]);
        ret = max(ret , white[N][j]);
    }
    return ret;
}

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d %d %d" , &segs[i].l , &segs[i].r , &segs[i].t);
        --segs[i].t;
        tmp.push_back(segs[i].l);
        tmp.push_back(segs[i].r);
    }
    init();
    printf("%d\n" , solve());
}