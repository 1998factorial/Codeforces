#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3fffffff;
const int maxn = 2005;
// Hungarian , find maximal cost matching
struct KM {
    // warning !! nx <= ny, otherwise, TLE!!!!!!
    int G[maxn][maxn];
    int m;
    int nx,ny;
    int link[maxn],lx[maxn],ly[maxn];
    int slack[maxn];
    bool visx[maxn],visy[maxn];
    
    bool dfs(int x) {
        visx[x]=1;
        for(int y=0;y<ny;y++){
            if(visy[y]) continue;
            int tmp=lx[x]+ly[y]-G[x][y];
            if(tmp==0){
                visy[y]=1;
                if(link[y]==-1||dfs(link[y])){
                    link[y]=x;
                    return true;
                }
            }
            else if(slack[y]>tmp) slack[y]=tmp;
        }
        return false;
    }
    
    int km() {
        memset(link,-1,sizeof(link));
        memset(ly,0,sizeof(ly));
        for(int i=0;i<nx;i++){
            lx[i]=-inf;
            for(int j=0;j<ny;j++){
                if(G[i][j]>lx[i]) lx[i]=G[i][j];
            }
        }
        for(int x=0;x<nx;x++){
            for(int i=0;i<ny;i++) slack[i]=inf;
            while(1){
                memset(visx,0,sizeof(visx));
                memset(visy,0,sizeof(visy));
                if(dfs(x)) break;
                int d=inf;
                for(int i=0;i<ny;i++){
                    if(!visy[i]&&d>slack[i]) d=slack[i];
                }
                for(int i=0;i<nx;i++){
                    if(visx[i]) lx[i]-=d;
                }
                for(int i=0;i<ny;i++){
                    if(visy[i]) ly[i]+=d;
                    else slack[i]-=d;
                }
            }
        }
        int res=0;
        for(int i=0;i<ny;i++){
            if(link[i]!=-1) res+=G[link[i]][i];
        }
        return res;
    }
} solver;

int N , M; // N wines , M bottles
array<int , 2> bottles[maxn] , car[maxn] , R;
int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 0; i < N; ++i){
        scanf("%d %d" , &bottles[i][0] , &bottles[i][1]);
    }
    for(int i = 0; i < M; ++i){
        scanf("%d %d" , &car[i][0] , &car[i][1]);
    }
    scanf("%d %d" , &R[0] , &R[1]);
    solver.nx = N;
    solver.ny = M + N - 1;
    auto dis = [&](array<int , 2> a , array<int , 2> b){
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);
    };
    for(int x = 0; x < solver.nx; ++x){
        for(int y = 0; y < solver.ny; ++y){
            if(y < M){
                solver.G[x][y] = -dis(bottles[x] , car[y]);
                solver.G[x][y] -= dis(bottles[x] , R);
            }
            else{
                solver.G[x][y] = -2 * dis(bottles[x] , R); 
            }
        }
    }
    /*
    wiki example
    solver.nx = 3 , solver.ny = 3;
    solver.G[0][0] = -2; solver.G[0][1] = -3; solver.G[0][2] = -3;
    solver.G[1][0] = -3; solver.G[1][1] = -2; solver.G[1][2] = -3;
    solver.G[2][0] = -3; solver.G[2][1] = -3; solver.G[2][2] = -2;
    we get -6
    */
    printf("%d\n" , -solver.km());
}