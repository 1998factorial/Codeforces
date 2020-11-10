/*
    Dynamic programming

    a[i] , b[i] are non negative, so we can should summon as many minions as possible
    We can keep K minions to maximise the sum of a[i]s, and in optimal solution, we can always
    kill N - K minions
    so, we should find which K minions that we are not going to kill
    sort by b[i], we know that if b[i] < b[i + 1] then we should summon i + 1 th minion after i th .
    as if there are j minions alive and hired we get b[i + 1] * j instead of b[i] * j

    DP[i][j] = maximal cost to hire j minions in the first i
    DP[i][j] = DP[i - 1][j - 1] + (j - 1) * b[i] + a[i]
    if we hire the ith and do not kill it
    DP[i][j] = DP[i - 1][j] + (K - 1) * b[i]
    if we hire the ith and kill it (then we should hire him after we decided the K - 1 th alive minion)
*/
#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 10;
int DP[76][76];
int keep[76][76]; // 0 if at this state, the ith minion is killed, 1 if keep alive
int N , K;
int a[76] , b[76];

struct minion{
    int a , b , id;
    minion(){}
    bool operator< (const minion& rhs) const {
        return b < rhs.b;
    }
} minions[76];

int main(){
    int t; cin >> t;
    while(t--){
        cin >> N >> K;
        for(int i = 1; i <= N; ++i){
            cin >> minions[i].a >> minions[i].b;
            minions[i].id = i;
        }
        sort(minions + 1 , minions + 1 + N);
        for(int i = 0; i <= N; ++i){
            for(int j = 0; j <= K; ++j){
                DP[i][j] = -inf;
                keep[i][j] = 0;
            }
        }
        DP[0][0] = 0;
        for(int i = 1; i <= N; ++i){
            for(int j = 0; j <= K; ++j){
                if(j > 0){ // ith keep alive
                    int v1 = DP[i - 1][j - 1] + (j - 1) * minions[i].b + minions[i].a;
                    if(v1 > DP[i][j]){
                        DP[i][j] = v1;
                        keep[i][j] = 1;
                    }
                }
                // we hire the ith and kill it :)
                int v2 = DP[i - 1][j] + (K - 1) * minions[i].b;
                if(v2 > DP[i][j]){
                    DP[i][j] = v2;
                    keep[i][j] = 0;
                }
            }
        }
        vector<int> alive , dead;
        int k = K;
        for(int i = N; i >= 1; --i){
            if(keep[i][k]){
                alive.push_back(minions[i].id);
            }
            else{
                dead.push_back(minions[i].id);
            }
            k -= keep[i][k];
        }
        reverse(alive.begin() , alive.end());
        cout << alive.size() + dead.size() * 2 << endl;
        for(int i = 0; i < K - 1; ++i){
            cout << alive[i] << " ";
        }
        for(int i : dead){
            cout << i << " " << -i << " ";
        }
        cout << alive.back() << endl;
    }
}
