#pragma warning(disable:4996)
#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef pair<double, int>pdi;
#define ll long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define _for(i, a, b) for (int i = a; i < b; ++i)
const int  mod = (int)1e9 + 7;
const int  maxn = 2005;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
struct node
{
    int x, y;
};
struct bc_edge {
    int dif, bottle, cart;
    bool operator<(const bc_edge & r) const {
        return dif < r.dif;
    }
};
int cal_dist(node l, node r) {
    return abs(l.x - r.x) + abs(l.y - r.y);
}
node a[maxn], b[maxn];
int dis[maxn];
const int N = 2005;
const int INF = 0x3f3f3f3f;
int nx, ny;//兩邊的點數
int g[N][N];//二分圖描述
int linker[N], lx[N], ly[N];//y中各點匹配狀態，x,y中的點標號
int slack[N];
bool visx[N], visy[N];
bool DFS(int x)
{
    visx[x] = true;
    for (int y = 0; y < ny; y++)
    {
        if (visy[y])continue;
        int tmp = lx[x] + ly[y] - g[x][y];
        if (tmp == 0)
        {
            visy[y] = true;
            if (linker[y] == -1 || DFS(linker[y]))
            {
                linker[y] = x;
                return true;
            }
        }
        else if (slack[y] > tmp)
            slack[y] = tmp;
    }
    return false;
}
int KM()
{
    memset(linker, -1, sizeof(linker));
    memset(ly, 0, sizeof(ly));
    for (int i = 0; i < nx; i++)
    {
        lx[i] = -INF;
        for (int j = 0; j < ny; j++)
            if (g[i][j] > lx[i])
                lx[i] = g[i][j];
    }
    for (int x = 0; x < nx; x++)
    {
        for (int i = 0; i < ny; i++)
            slack[i] = INF;
        while (true)
        {
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if (DFS(x))break;
            int d = INF;
            for (int i = 0; i < ny; i++)
                if (!visy[i] && d > slack[i])
                    d = slack[i];
            for (int i = 0; i < nx; i++)
                if (visx[i])
                    lx[i] -= d;
            for (int i = 0; i < ny; i++)
            {
                if (visy[i])ly[i] += d;
                else slack[i] -= d;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < ny; i++)
        if (linker[i] != -1)
            res += g[linker[i]][i];
    return res;
}

int main() {
    int n, m;
    int ans = 0;
    node t;
    scanf("%d%d", &n, &m);
    _for(i, 0, n)
        scanf("%d%d", &a[i].x, &a[i].y);
    _for(i, 0, m)
        scanf("%d%d", &b[i].x, &b[i].y);
    scanf("%d%d", &t.x, &t.y);
    _for(i, 0, n) {
        dis[i] = cal_dist(t, a[i]);
        ans += 2 * dis[i];
    }
    // cout << ans << endl;
    vector<bc_edge> v;
    _for(i, 0, n) {
        _for(j, 0, m) {
            int tmp = cal_dist(a[i], b[j]) - dis[i];
            v.push_back({ tmp, i, j });
        }
    }
    sort(begin(v), end(v));
    for (int i = 0; i < (int)v.size(); ++i) {
        if (v[i].dif < 0) {
            int x = v[i].bottle;
            int y = v[i].cart;
            g[x][y] = -v[i].dif;
        }
        else
            break;
    }
    nx = n + m, ny = n + m;
    int tmp = -v[0].dif;
    if (v[0].dif < 0) {
        tmp = KM();
    }
    printf("%d\n", ans - tmp);
    return 0;
}