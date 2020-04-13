#include <iostream>
#include <cstdio>
#include <string>
#include <sstream> 
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;
//1<=n<=150
//0<=m<=n(n-1)
typedef long long ll;
const int maxn = 205;
//dp[l][r][k] = "
//maximal score to remove a[l..r] where the maximal appear sum is accumulated k times"

ll a[maxn],dp[maxn][maxn][maxn],sum[maxn];
int L[maxn],R[maxn];
bool d[maxn][maxn],seen[maxn][maxn][maxn];
int n,m,x,y;

ll solve(int l, int r, int k){
    if(r<l)return 0ll;
    if(seen[l][r][k])return dp[l][r][k];
    ll ret=(ll)-1e18;
    if(l==r)ret=max(0ll,a[l])*(ll)k;
    else{
        ll S=sum[r+1]-sum[l],Sx=0ll;
        for(int p=l;p<=r;p++){
            if(L[p] < l && R[p] > r){
                ret=max(ret,solve(l,p-1,r-p+k)+solve(p+1,r,k)+Sx);
                ret=max(ret,solve(l,p-1,r-p)+solve(p+1,r,0)+Sx+(ll)k*S);
            }
            Sx+=a[p];
        }
    }
    seen[l][r][k]=true;
    return dp[l][r][k]=ret;
}

int main(){
    memset(d,false,sizeof(d));
    memset(seen,false,sizeof(seen));
    cin>>n;for(int i=0;i<n;i++)cin>>a[i];
    cin>>m;for(int i=0;i<m;i++)cin>>x>>y,x--,y--,d[x][y]=true;
    sum[0]=0;for(int i=0;i<n;i++)sum[i+1]=sum[i]+a[i];
    for(int i=0;i<n;i++){
        L[i]=-1;
        for(int j=0;j<i;j++)if(d[j][i])L[i]=j;
        R[i]=n+1;
        for(int j=n-1;j>i;j--)if(d[j][i])R[i]=j;
    }
    ll ret=solve(0,n-1,0);
    if(ret<(ll)-5e17)cout<<"Impossible\n";
    else cout<<ret<<endl;
    return 0;
}
