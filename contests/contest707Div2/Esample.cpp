#include<bits/stdc++.h>
using namespace std;
const int N=1505;
int a[N][N],b[N][N],f[N][N],deg[N],vis[N];
queue<int>Q;
vector<int>vec;
vector<int>cmp[2];
int num[N],pos[N][5005];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    int s=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&b[i][j]),s|=b[i][j]!=a[i][j];
    for(int i=1;i<=m;i++){
        cmp[0].clear(),cmp[1].clear();
        for(int j=1;j<=n;j++)
            cmp[0].push_back(a[j][i]),cmp[1].push_back(b[j][i]);
        sort(cmp[0].begin(),cmp[0].end());sort(cmp[1].begin(),cmp[1].end());
        for(int i=0;i<n;i++)
            if(cmp[0][i]!=cmp[1][i])
                return 0*printf("-1\n");
    }
    if(!s)return 0*printf("0\n");
    for(int j=1;j<=m;j++){
        for(int i=1;i<n;i++)
            deg[j]+=b[i][j]>b[i+1][j];
        if(!deg[j])Q.push(j);
    }
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        vec.push_back(u);
        for(int i=1;i<n;i++){
            if(!vis[i]&&b[i][u]<b[i+1][u]){
                for(int j=1;j<=m;j++){
                    if(b[i][j]>b[i+1][j]){
                        deg[j]--;
                        if(!deg[j])Q.push(j);
                    }
                }
                vis[i]=1;
            }
        }
    }
    int sz=vec.size();
    for(int i=1;i<=n;i++)pos[sz][i]=i;
    for(int i=sz-1;~i;i--){
        int u=vec[i];
        memset(num,0,sizeof(num));
        for(int j=1;j<=n;j++)num[a[j][u]]++;
        for(int j=2;j<=n;j++)num[j]+=num[j-1];
        for(int j=n;j;j--)
            pos[i][num[a[pos[i+1][j]][u]]--]=pos[i+1][j];
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[pos[0][i]][j]!=b[i][j])
                return 0*printf("-1\n");
    printf("%d\n",sz);
    for(int i=sz-1;~i;i--)
        printf("%d ",vec[i]);
    printf("\n");
    return 0;
}