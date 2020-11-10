/*
    Hungarian will do the job , which is much faster 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

ll hungarian(vector<vector<ll>> costs) {

    int n = int(costs.size());
    int m = costs.empty() ? 0 : int(costs[0].size());

    if (n > m) {
        vector<vector<ll>> new_costs(m, vector<ll>(n));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                new_costs[j][i] = costs[i][j];

        swap(costs, new_costs);
        swap(n, m);
    }

    vector<ll> u(n + 1), v(m + 1);
    vector<int> p(m + 1), way(m + 1);
    vector<int> assignment;

    for (int i = 1; i <= n; i++) {
        vector<ll> min_v(m + 1, INF);
        vector<bool> used(m + 1, false);
        p[0] = i;
        int j0 = 0;

        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            ll delta = INF;

            for (int j = 1; j <= m; j++)
                if (!used[j]) {
                    ll cur = costs[i0 - 1][j - 1] - u[i0] - v[j];

                    if (cur < min_v[j]) {
                        min_v[j] = cur;
                        way[j] = j0;
                    }

                    if (min_v[j] < delta) {
                        delta = min_v[j];
                        j1 = j;
                    }
                }

            for (int j = 0; j <= m; j++)
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    min_v[j] -= delta;
                }

            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }
    // Note that p[j] is the row assignment of column j (both 1-based). If p[j] = 0, the column is unassigned.
    assignment = p;
    return -v[0];
}

int N , a[505] , b[505] , k[505];

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d %d %d" , &a[i] , &b[i] , &k[i]);
    }
    vector<vector<ll>> costs(N , vector<ll>(N));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            ll val = (ll)a[i + 1] - (ll)min(N - j - 1 , k[i + 1]) * b[i + 1];
            val = min(0ll , -val);
            costs[i][j] = val;
        }
    }
    ll ret = -hungarian(costs);
    printf("%lld\n" , ret);
}
