#include<stdio.h>  
#include<string.h>  
#define NN 256  
#define mod 1000000000  
typedef long long ll;
struct matrix  //设定为NN*NN的矩阵  
{
	ll mat[NN][NN];
}a, ans, c, d;
ll f[10];
ll n, m;
matrix operator	*(matrix a, matrix b) {
	matrix c;
	memset(c.mat, 0, sizeof(c.mat));
	for (ll i = 0; i<NN; i++) {
		for (ll k = 0; k<NN; k++) {
			if (a.mat[i][k] == 0)continue;
			for (ll j = 0; j<NN; j++)
				c.mat[i][j] = (c.mat[i][j] + (a.mat[i][k] % mod)*(b.mat[k][j] % mod)) % mod;
		}
	}
	return c;
}
matrix qpow(ll b)
{
	memset(d.mat, 0, sizeof(d.mat));
	for (ll i = 0; i<NN; i++) {
		for (ll j = 0; j<NN; j++) {
			if (i == j) d.mat[i][j] = 1;
			else d.mat[i][j] = 0;
		}
	}
	while (b>0) {
		if (b % 2 == 1)d = d * a;
		a = a * a;
		b >>= 1;
	}
	return d;
}
void dfs(ll pos, ll now, ll to) {
	if (pos >= n) {
		a.mat[now][to]++;
		return;
	}
	if (now&(1 << pos)) {
		dfs(pos + 1, now, to);
		dfs(pos + 1, now, to + f[pos]);
		if (pos + 1<n && (now&(1 << (pos + 1))))
			dfs(pos + 2, now, to + f[pos] + f[pos + 1]);
	}
	else dfs(pos + 1, now, to + f[pos]);
}
int main() {
	f[0] = 1;
	for (ll i = 1; i<10; i++)f[i] = f[i - 1] * 2;
	scanf("%lld%lld", &n, &m);
	for (ll state = 0; state<(1 << n); state++)
		dfs(0, state, 0);
	for (ll i = 0; i<(1 << n); i++)
		ans.mat[0][i] = a.mat[(1 << n) - 1][i];
	a = qpow(m - 1);
	ans = ans * a;
	printf("%lld\n", ans.mat[0][(1 << n) - 1]);
	return 0;
}