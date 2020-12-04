#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
//using namespace __gnu_pbds;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define fbo find_by_order
#define ook order_of_key

typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<int> vi;
typedef long double ld;
//typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds;

const int MX = 123;
const int INF = int(1e9);
struct MaxFlow //by yutaka1999, have to define INF and MX (the Max number of vertices)
{
	struct edge
	{
		int to,cap,rev;
		edge(int to=0,int cap=0,int rev=0):to(to),cap(cap),rev(rev){}
	};
	vector <edge> vec[MX];
	int level[MX];
	int iter[MX];

	void addedge(int s,int t,int c) //adds an edge of cap c to the flow graph
	{
		int S=vec[s].size(),T=vec[t].size();
		vec[s].push_back(edge(t,c,T));
		vec[t].push_back(edge(s,0,S));
	}
	void bfs(int s)
	{
		memset(level,-1,sizeof(level));
		queue <int> que;
		level[s] = 0;
		que.push(s);
		while (!que.empty())
		{
			int v = que.front();que.pop();
			for(int i=0;i<vec[v].size();i++)
			{
				edge&e=vec[v][i];
				if (e.cap>0&&level[e.to]<0)
				{
					level[e.to]=level[v]+1;
					que.push(e.to);
				}
			}
		}
	}
	ll flow_dfs(int v,int t,ll f)
	{
		if (v==t) return f;
		for(int &i=iter[v];i<vec[v].size();i++)
		{
			edge &e=vec[v][i];
			if (e.cap>0&&level[v]<level[e.to])
			{
				ll d=flow_dfs(e.to,t,min(f,ll(e.cap)));
				if (d>0)
				{
					e.cap-=d;
					vec[e.to][e.rev].cap+=d;
					return d;
				}
			}
		}
		return 0;
	}
	ll maxflow(int s,int t) //finds max flow using dinic from s to t
	{
		ll flow = 0;
		while(1)
		{
			bfs(s);
			if (level[t]<0) return flow;
			memset(iter,0,sizeof(iter));
			while (1)
			{
				ll f=flow_dfs(s,t,INF);
				if(f==0) break;
				flow += f;
			}
		}
	}
};

int a[55][55];
const bool DEBUG=0;

bool check(int n, int k)
{
	int sum=0;
	for(int i=0;i<n;i++)
	{
		set<int> S;
		for(int j=0;j<n;j++)
		{
			S.insert(a[i][j]);
			//assert(a[i][j]>=1&&a[i][j]<=n);
		}
		sum+=a[i][i];
		if(S.size()!=n) return false;
		S.clear();
		for(int j=0;j<n;j++)
		{
			S.insert(a[j][i]);
		}
		if(S.size()!=n) return false;
	}
	return (sum==k);
}

void go(int u, int n)
{
  cout << "go " << u << endl;
	int s=MX-1; int e=MX-2;
	MaxFlow mf;
	bitset<100> rows;
	bitset<100> cols;
	rows.reset(); cols.reset();
	int res=n;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(a[i][j]==u)
			{
				rows.set(i,1); cols.set(j,1);
				res--;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		if(!rows[i]) mf.addedge(s,i,1) , printf("connecting %d -> %d\n" , s , i);
		if(!cols[i]) mf.addedge(i+n,e,1) , printf("connecting %d -> %d\n" , i + n , e);
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(a[i][j]==-1)
			{
				mf.addedge(i,j+n,1);
        printf("conneceting %d -> %d\n" , i , j + n);
			}
		}
	}
	int flow = mf.maxflow(s,e);
	//assert(flow==res);
	for(int i=0;i<n;i++)
	{
		for(auto e : mf.vec[i])
		{
			if(e.to>=n&&e.to<2*n&&e.cap==0)
			{
				a[i][e.to-n]=u;
        printf("setting (%d , %d) = %d\n" , i , e.to - n , u);
				flow--;
			}
		}
	}
	//assert(flow==0);
}

void solve(int cc, int N=0, int K=0)
{
	int n,k;
	if(!DEBUG) cin>>n>>k;
	else n=N,k=K;
	memset(a,-1,sizeof(a));
	if(!DEBUG)
	{
		cout<<"Case #"<<cc<<": ";
	}
	if(k==n*n-1||k==n+1||(n==3&&k==5)||(n==3&&k==7)){if(!DEBUG){cout<<"IMPOSSIBLE\n";} return ;}
	//greedy a diagonal, spam max flow lul?
	//condition: the diagonal does not have n-1 copies of the same element
	for(int i=0;i<n;i++)
	{
		a[i][i]=k/n;
	}
	int r = k%n;
	if(r>1&&n-r>1)
	{
		for(int i=0;i<r;i++)
		{
			a[i][i]++;
		}
	}
	else if(r==1)
	{
		//assert(n>=3);
		a[0][0]++; a[1][1]++; a[2][2]--;
	}
	else if(r==n-1)
	{
		for(int i=0;i<n;i++)
		{
			a[i][i]++;
		}
		//assert(n>=3);
		a[0][0]--; a[1][1]--; a[2][2]++;
		//assert(a[2][2]<=n);
	}
	vector<ii> vec;
	map<int,int> ma;
	for(int i=0;i<n;i++)
	{
		ma[a[i][i]]++;
		//cerr<<"DIAGONAL "<<i<<" = "<<a[i][i]<<'\n';
	}
	for(int i=1;i<=n;i++)
	{
		vec.pb({ma[i],i});
	}
	sort(vec.rbegin(),vec.rend());
	for(ii v:vec)
	{
		go(v.se,n);
		//cerr<<"FILLED "<<v.se<<" SUCCESSFULLY\n";
	}
	//assert(check(n,k));
	if(!DEBUG)
	{
		cout<<"POSSIBLE\n";
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				cout<<a[i][j];
				if(j+1<n) cout<<' ';
			}
			cout<<'\n';
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	if(!DEBUG)
	{
		int t; cin>>t;
		for(int cc=1;cc<=t;cc++) solve(cc);
	}
	else
	{
		for(int n=2;n<=50;n++)
		{
			for(int k=n;k<=n*n;k++)
			{
				solve(0,n,k);
				cerr<<"Case "<<n<<' '<<k<<" solved.\n";
			}
		}
	}
}
