#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int N =2e5+9;
int n,k;
int head[N],nex[2*N],to[2*N],now;
void add(int a,int b){
    to[++now]=b;nex[now]=head[a];head[a]=now;
}
int a[N];
LL ans[N];
inline int gcd(int a , int b){
    return a == 0 ? b : gcd(b % a , a);
}
int G;
int vis[N];//是否删除
int siz[N],maxn[N];//这棵子树大小，最大子树大小
void getG(int p,int fa,int sum){
    siz[p]=1;
    maxn[p]=0;
    for(int i=head[p];~i;i=nex[i]){
        if(!vis[to[i]]&&to[i]!=fa){
            getG(to[i],p,sum);//这个时候既可以得出G，又可以得出下面的siz
            siz[p]+=siz[to[i]];
            maxn[p]=max(maxn[p],siz[to[i]]);//找出最大子树
        }
    }
    maxn[p]=max(maxn[p],sum-siz[p]);//当然还要这棵树的上半部分比较
    if(maxn[G]>maxn[p])G=p;
}

int dep[N],num,len[N];
int t1[N],t2[N];
void dfs(int p,int fa){
    for(int i=head[p];~i;i=nex[i]){
        if(vis[to[i]]||fa==to[i])continue;
        len[++num]=dep[to[i]]=gcd(dep[p],a[to[i]]);
        dfs(to[i],p);
    }
}
void cal(int p,int mul,int flag){//重点，多加的部分的消除
    num=0;
    len[++num]=dep[p]=gcd(mul,a[p]);//自己也加进去
    dfs(p,0);//得出离G点距离
    sort(len+1,len+1+num);
    printf("at %d\n" , p);
    for(int i = 1; i <= num; ++i){
        printf("%d " , len[i]);
    }
    printf("\n");
    int ct=0;
    rep(i,1,num){
        if(i>1&&len[i]==len[i-1])t2[ct]++;
        else {
            t1[++ct]=len[i];
            t2[ct]=1;
        }
    }
    rep(i,1,ct){
        if(t2[i]>1){
            ans[t1[i]]+=1ll*flag*(t2[i]-1)*t2[i]/2;
        }
        rep(j,i+1,ct){
            ans[gcd(t1[i],t1[j])]+=1ll*flag*t2[i]*t2[j];
        }
    }
}

void divide(int p){
    //printf("centroid %d\n" , p);
    vis[p]=1;
    cal(p,a[p],1);
    for(int i=head[p];~i;i=nex[i]){
        if(vis[to[i]])continue;
        cal(to[i],a[p],-1);
        G=0;//为了初始化
        maxn[0]=siz[to[i]];
        getG(to[i],0,siz[to[i]]);//一套做全都是0
        divide(G);
    }
}

int main(){
    memset(head,-1,sizeof head);
    now=0;
    int n;scanf("%d",&n);
    maxn[0]=n;
    rep(i,1,n){
        scanf("%d",a+i);
        ans[a[i]]++;
    }
    rep(i,1,n-1){
        int x,y;scanf("%d%d",&x,&y);
        add(x,y),add(y,x);
    }
    G=0;
    getG(1,0,n);
    divide(G);
    rep(i,1,2e5){
        if(ans[i]){
            printf("%d %lld\n",i,ans[i]);
        }
    }
}