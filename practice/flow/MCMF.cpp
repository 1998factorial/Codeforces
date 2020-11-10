#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

struct MCMF{

    struct Edge{
    	int to,next,flow,dis;//flow流量 dis花费
    } edge[maxn];

    bool vis[maxn];
    int head[maxn];
    int num_edge;
    queue <int> q;
    int n , m , s , t , x , y , z , f;
    int dis[maxn] , pre[maxn] , last[maxn] , flow[maxn];
    int maxflow , mincost;
    //dis最小花费;pre每个点的前驱；last每个点的所连的前一条边；flow源点到此处的流量

    void init(int n_ , int m_ , int s_ , int t_){
        memset(head,-1,sizeof(head));
        num_edge = -1;//初始化
        n = n_; m = m_; s = s_; t = t_;
    }

    void add_edge(int from , int to , int flow , int dis){
    	edge[++num_edge].next = head[from];
    	edge[num_edge].to = to;
    	edge[num_edge].flow = flow;
    	edge[num_edge].dis = dis;
    	head[from] = num_edge;
    }

    void add(int from , int to , int flow , int cost){
        add_edge(from , to , flow , cost);
        add_edge(to , from , 0 , -cost);
        //反边的流量为0，花费是相反数
    }

    bool spfa(int s,int t){
    	memset(dis,0x7f,sizeof(dis));
    	memset(flow,0x7f,sizeof(flow));
    	memset(vis,0,sizeof(vis));
    	q.push(s);
        vis[s] = 1; dis[s] = 0; pre[t] = -1;
    	while (!q.empty()){
    		int now = q.front();
    		q.pop();
    		vis[now] = 0;
    		for (int i = head[now]; i != -1; i = edge[i].next){
    			if (edge[i].flow > 0 && dis[edge[i].to] > dis[now] + edge[i].dis){//正边
    				dis[edge[i].to] = dis[now] + edge[i].dis;
    				pre[edge[i].to] = now;
    				last[edge[i].to] = i;
    				flow[edge[i].to] = min(flow[now] , edge[i].flow);//
    				if (!vis[edge[i].to]){
    					vis[edge[i].to] = 1;
    					q.push(edge[i].to);
    				}
    			}
    		}
    	}
    	return pre[t] != -1;
    }

    vector<int> getMCMF(){
        maxflow = 0;
        mincost = 0;
    	while (spfa(s,t)){
    		int now = t;
    		maxflow += flow[t];
    		mincost += flow[t] * dis[t];
    		while (now != s){//从源点一直回溯到汇点
    			edge[last[now]].flow -= flow[t];//flow和dis容易搞混
    			edge[last[now]^1].flow += flow[t];
    			now = pre[now];
    		}
    	}
        return {maxflow , mincost};
    }

};

int n , m , s , t;

int main(){
    MCMF G;
	scanf("%d %d %d %d", &n , &m , &s , &t);
    G.init(n , m , s , t);
	for (int i = 1; i <= m; i++){
        int x , y , z , f;
		scanf("%d %d %d %d", &x , &y , &z , &f);
        G.add(x , y , z , f);
	}
	vector<int> ret = G.getMCMF();
	printf("%d %d", ret[0] , ret[1]);
	return 0;
}
