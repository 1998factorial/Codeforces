#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define sqz main
#define ll long long
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define travel(i, u) for (int i = head[u]; i; i = edge[i].next)
const int INF = 1e9, mo = 1e9 + 7, N = 5005;
const double eps = 1e-6, phi = acos(-1.0);
ll mod(ll a, ll b) {if (a >= b || a < 0) a %= b; if (a < 0) a += b; return a;}
ll read(){ ll x = 0; int zf = 1; char ch; while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
if (ch == '-') zf = -1, ch = getchar(); while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;}
void write(ll y) { if (y < 0) putchar('-'), y = -y; if (y > 9) write(y / 10); putchar(y % 10 + '0');}
int f[N][N], g[N][N], f_sum[N][N], g_min[N][N], T[N], S[N], mi[N], Same[N][N];
char st[N];
int cmp(int b1, int b2, int len)
{
	int t = Same[b1][b2];
	if (t >= len) return 1;
	return T[b1 + t] < T[b2 + t];
}
int sqz() 
{
	scanf("%s", st + 1);
	int n = strlen(st + 1);
	rep(i, 1, n) T[i] = st[i] - '0';
	mi[0] = 1;
	rep(i, 1, n)
	{
		S[i] = (S[i - 1] * 2 + T[i]) % mo;
		mi[i] = mi[i - 1] * 2 % mo;
	} 
	per(i, n, 1)
		per(j, n, 1)
			if (T[i] == T[j]) Same[i][j] = Same[i + 1][j + 1] + 1;
			else Same[i][j] = 0;
	rep(i, 1, n)
	{
		f[i][0] = f_sum[i][0] = g[i][0] = g_min[i][0] = 1;
		rep(j, 1, i - 1)
		{
			g[i][j] = g_min[i][j] = INF;
			if (T[j + 1] == 1)
			{
				int k = j - (i - j);
				if (k < -1) k = -1;
				f[i][j] = (f[i][j] + f_sum[j][k + 1]) % mo;
				g[i][j] = min(g[i][j], g_min[j][k + 1] + 1) % mo;
				if (k + 1 && T[k + 1] && cmp(k + 1, j + 1, i - j))
				{
					f[i][j] = (f[i][j] + f[j][k]) % mo;
					g[i][j] = min(g[i][j], g[j][k] + 1) % mo;
				}
				f_sum[i][j] = (f_sum[i][j] + f[i][j])  % mo;
				g_min[i][j] = min(g_min[i][j], g[i][j]);
			}
		}
		g_min[i][i] = INF;
		per(j, i - 1, 0)
		{
			f_sum[i][j] = (f_sum[i][j] + f_sum[i][j + 1])% mo;
			g_min[i][j] = min(g_min[i][j], g_min[i][j + 1]);
		}
	}
	int ans = INF;
	rep(i, 1, min(16, n)) ans = min(ans, g[n][n - i] + (int)((S[n] - (ll)S[n - i] * mi[i]) % mo + mo) % mo) % mo;
	if (ans == INF)
		rep(i, 17, n)
			if (g[n][n - i] != INF)
			{
				ans = g[n][n - i] + (int)((S[n] - (ll)S[n - i] * mi[i]) % mo + mo) % mo;
				break;
			}
	printf("%d\n%d\n", f_sum[n][0], ans);
}