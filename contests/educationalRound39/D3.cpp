#include <cstdio>
#include <iostream>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 505;
const ll mod = 1e9+7;
const ll INF = 1e18;
const double eps = 1e-9;

char s[maxn];
int num[maxn][maxn];
int dp[maxn][maxn];
vector<int>vec[maxn];

int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        int len=strlen(s+1);
        for(int j=1;j<=len;j++)
        {
            if(s[j]=='1') vec[i].push_back(j);
        }
    }
    for(int i=1;i<=n;i++)
    {
        int tmp=vec[i].size();
        if(tmp==0) continue;
        for(int len=1;len<=tmp;len++)
        {
            int Min=vec[i][len-1]-vec[i][0]+1;
            for(int j=0;j+len-1<tmp;j++)
            {
                Min=min(Min,vec[i][j+len-1]-vec[i][j]+1);
            }
            num[i][tmp-len]=Min;
        }
    }
    for(int i=0;i<=k;i++) dp[1][i]=num[1][i];
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<=k;j++)
        {
            int Min=dp[i-1][j]+num[i][0];
            for(int o=0;o<=j;o++)
            {
                Min=min(Min,dp[i-1][j-o]+num[i][o]);
            }
            dp[i][j]=Min;
        }
    }
    for(int i = 0; i <= n; ++i){
      for(int j = 0; j <= k; ++j){
        printf("dp[%d][%d] = %d\n" , i , j , dp[i][j]);
      }
    }
    printf("%d\n",dp[n][k]);
}
