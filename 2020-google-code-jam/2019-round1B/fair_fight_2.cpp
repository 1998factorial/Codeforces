#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
ll a[maxn],b[maxn],n,ans,k,d[maxn],A[maxn][18],B[maxn][18];
ll qrya(int l,int r){
    int len=d[r-l+1];
    return max(A[l][len],A[r-(1<<len)+1][len]);
}
ll qryb(int l,int r){
    int len=d[r-l+1];
    return max(B[l][len],B[r-(1<<len)+1][len]);
}
int findla(int x,ll val){
    int l=0,r=x+1;
    while (r-l>1){
        int mid=(l+r)/2;
        if (qrya(mid,x)<val) r=mid; else l=mid;
    }
    return l;
}
int findlb(int x,ll val){
    int l=0,r=x+1;
    while (r-l>1){
        int mid=(l+r)/2;
        if (qryb(mid,x)<val) r=mid; else l=mid;
    }
    return l;
}
int findra(int x,ll val){
    int l=x-1,r=n+1;
    while (r-l>1){
        int mid=(l+r)/2;
        if (qrya(x,mid)<val) l=mid; else r=mid;
    }
    return r;
}
int findrb(int x,ll val){
    int l=x-1,r=n+1;
    while (r-l>1){
        int mid=(l+r)/2;
        if (qryb(x,mid)<val) l=mid; else r=mid;
    }
    return r;
}
int main(){
    for (int i=2;i<maxn;i++) d[i]=d[i/2]+1;
    int _,kase=0; cin >> _;
    while (_--){
        scanf("%lld%lld",&n,&k); ans=n*(n+1)/2;
        for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
        for (int i=1;i<=n;i++) scanf("%lld",&b[i]);
        for (int i=1;i<=n;i++) A[i][0]=a[i],B[i][0]=b[i];
        for (int j=1;j<18;j++)
            for (int i=1;i+(1<<j)-1<=n;i++)
                A[i][j]=max(A[i][j-1],A[i+(1<<(j-1))][j-1]),
                B[i][j]=max(B[i][j-1],B[i+(1<<(j-1))][j-1]);
        for (int i=1;i<=n;i++){
            int L=max(findla(i-1,a[i]+1),findlb(i-1,a[i]-k));
            int R=min(findra(i+1,a[i]),findrb(i+1,a[i]-k));
            if (a[i]-b[i]>k) ans-=(i-L)*1ll*(R-i);
        }
        for (int i=1;i<=n;i++){
            int L=max(findlb(i-1,b[i]+1),findla(i-1,b[i]-k));
            int R=min(findrb(i+1,b[i]),findra(i+1,b[i]-k));
            if (b[i]-a[i]>k) ans-=(i-L)*1ll*(R-i);
        }
        printf("Case #%d: %lld\n",++kase,ans);
    }
    return 0;
}
