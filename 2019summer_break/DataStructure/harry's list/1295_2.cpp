#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

const int maxn=2e5+5;

struct Tree
{
    int l,r;
    ll lazy,MIN;
}tree[maxn<<2];

int n;
int a[maxn],p[maxn],idx[maxn];
ll t[maxn];

inline void up(int i)
{
    tree[i].MIN=min(tree[i<<1].MIN,tree[i<<1|1].MIN);
}

inline void down(int i)
{
    int l=i<<1,r=i<<1|1;
    tree[l].lazy+=tree[i].lazy,tree[r].lazy+=tree[i].lazy;
    tree[l].MIN+=tree[i].lazy,tree[r].MIN+=tree[i].lazy;
    tree[i].lazy=0;
}

void build(int i,int l,int r)
{
    tree[i].l=l,tree[i].r=r,tree[i].lazy=0;
    if(l==r)
    {
        tree[i].MIN=t[l];
        return ;
    }
    int mid=l+r>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    up(i);
}

void update(int i,int l,int r,int v)
{
    if(tree[i].l==l&&tree[i].r==r)
    {
        tree[i].MIN+=v,tree[i].lazy+=v;
        return ;
    }
    if(tree[i].lazy)
        down(i);
    int mid=tree[i].l+tree[i].r>>1;
    if(mid>=r)
        update(i<<1,l,r,v);
    else if(mid<l)
        update(i<<1|1,l,r,v);
    else
        update(i<<1,l,mid,v),update(i<<1|1,mid+1,r,v);
    up(i);
}

ll query(int i,int l,int r)
{
    if(tree[i].l==l&&tree[i].r==r)
        return tree[i].MIN;
    if(tree[i].lazy)
        down(i);
    int mid=tree[i].l+tree[i].r>>1;
    if(mid>=r)
        return query(i<<1,l,r);
    else if(mid<l)
        return query(i<<1|1,l,r);
    else
        return min(query(i<<1,l,mid),query(i<<1|1,mid+1,r));
    up(i);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i]),idx[p[i]]=i;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        t[i]=t[i-1]+a[i];
    }
    build(1,1,n);
    int val=1,id;
    ll ans=query(1,1,n-1);
    while(val<=n)
    {
        id=idx[val];
        update(1,id,n,-a[id]);
        cout << "update " << id << " " << n << " with " << -a[id] << endl;
        if(id>1)
            update(1,1,id-1,a[id]) ,         cout << "update " << 1 << " " << id - 1 << " with " << a[id] << endl;
        ans=min(ans,query(1,1,n-1));
        cout << ans << endl;
        ++val;
    }
    printf("%lld\n",ans);
    return 0;
}
