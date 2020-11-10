#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const int inf = 1e9 + 10;

class ZhuLiu {

public:
    struct edge {
        int u, v, id;
        double cost, w;
    };
    struct Cancel {
        int pre, id;
    };

    vector<edge> e;
    vector<bool> isTreeEdge;

    int m,n,rt;

    ZhuLiu(int nn,int mm,int r) {
        n = nn;
        m = mm;
        rt = r;
    }

    void addEdge(int u, int v, double w) {
        e.push_back((edge){u,v,(int)e.size(),w,w});
    }

    double askMST() {
        int Nv = n,Ne = m,root = rt;
        double ret = 0;
        int total = m;
        vector<int> vis, pre, id, preid(n,0);
        vector<double> in;
        vector<int> useE(Ne,0);
        vector<Cancel> cancel(Ne);

        while (true) {
            useE.resize(total);
            in = vector<double>(Nv,inf);
            pre = vector<int>(Nv,-1);
            id = vector<int>(Nv,-1);
            vis = vector<int>(Nv,-1);

            for (int i = 0; i < Ne; i++) {
                int u = e[i].u, v = e[i].v;
                if (e[i].cost < in[v] && u != v) {
                    pre[v] = u;
                    in[v] = e[i].cost;
                    preid[v] = e[i].id;
                }
            }
            for (int i = 0; i < Nv; i++)
                if (i != root && in[i] == inf)
                    return -1;
            int cntnode = 0;
            in[root] = 0;
            for (int i = 0; i < Nv; i++) {
                ret += in[i];
                int v = i;
                if (i != root)
                    useE[preid[i]]++;
                while (vis[v] != i && id[v] == -1 && v != root)
                    vis[v] = i, v = pre[v];
                if (v != root && id[v] == -1) {
                    for (int u = pre[v]; u != v; u = pre[u])
                        id[u] = cntnode;
                    id[v] = cntnode++;
                }
            }
            if (cntnode == 0) break;
            for (int i = 0; i < Nv; i++)
                if (id[i] == -1)
                    id[i] = cntnode++;
            for (int i = 0; i < Ne; i++) {
                int u = e[i].u;
                int v = e[i].v;
                e[i].u = id[u];
                e[i].v = id[v];
                if (e[i].u != e[i].v) {
                    cancel.push_back((Cancel){preid[v],e[i].id});
                    e[i].cost -= in[v];
                    e[i].id = total++;
                }
            }
            Nv = cntnode;
            root = id[root];
        }
        for (int i = total - 1; i >= Ne; i--)
            if (useE[i]) {
                useE[cancel[i].pre]--;
                useE[cancel[i].id]++;
            }
        isTreeEdge = vector<bool>(m);
        for(int i = 0;i < m;i ++) {
            if(useE[i]) isTreeEdge[i] = 1;
        }
        return ret;
    }

    vector<bool> getEdgeCategory() {
        return isTreeEdge;
    }

};


int main(){
    //DO some thing
}
