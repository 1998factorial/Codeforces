#include <bits/stdc++.h>
using namespace std;
int N , M;
int can[1005];

int query(int h , int w , int i1 , int j1 , int i2 , int j2){
    cout << "? " << h << " " << w << " " << i1 << " " << j1 << " " << i2 << " " << j2 << endl;
    cout.flush();
    int ret;
    cin >> ret;
    return ret;
}

int gcd(int a , int b){
    return a == 0 ? b : gcd(b % a , a);
}

int check(vector<vector<int>> t , int l , int r , int m , int row){
    if(l >= r)return 1;
    int cnt = (r - l + 1) / 2; // ceil
    int h = t[l + cnt - 1][2] - t[l][0] + 1;
    int w = m;
    if(!row){
        h = m;
        w = t[l + cnt - 1][3] - t[l][1] + 1;
    }
    int i1 = t[l][0];
    int j1 = t[l][1];
    int i2 = t[l + cnt][0];
    int j2 = t[l + cnt][1];
    int v = query(h , w , i1 , j1 , i2 , j2);
    if(v){
        return check(t , l + cnt , r , m , row);
    }
    return 0;
}

int solve_row(){
    for(int i = 1; i <= N; ++i)can[i] = -1;
    for(int i = N; i >= 1; --i){
        if(~can[i])continue;
        if(N % i != 0)continue;
        for(int j = 2 * i; j <= N; j += i){
            if(N % j != 0)continue;
            // we know can[j] = 1
            // so we only need to check if we can split 
            // the first j by M matrix into some i by M matrix
            vector<vector<int>> t;
            for(int k = 1; k <= j / i; ++k){
                int r1 = (k - 1) * i + 1;
                int c1 = 1;
                int r2 = k * i;
                int c2 = 1;
                t.push_back({r1 , c1 , r2 , c2});
            }
            if(check(t , 0 , t.size() - 1 , M , 1))can[i] = 1;
            else can[i] = 0;
            break;
        }
        if(can[i] == 0){
            // if we can not split the matrix into i blocks
            // then we can not split the matrix into j blocks
            // if j | i
            for(int j = 1; j <= N; ++j){
                if(i % j == 0){
                    can[j] = 0;
                }
            }
        }
        else{
            // if we can split the matrix into i blocks and j blocks
            // then we can split the matrix into k * gcd(i , j) blocks
            // where k * gcd(i , j) | N
            can[i] = 1;
            for(int j = 1; j <= N; ++j){
                if(can[j] == 1){
                    int d = gcd(i , j);
                    for(int dd = d; dd <= N; dd += d){
                        if(N % dd == 0){
                            can[dd] = 1;
                        }
                    }
                }
            }
        }
    }
    int ret = 0;
    for(int i = 1; i <= N; ++i){
        if(can[i] == 1 && N % i == 0){
            ++ret;
        }
    }
    return ret;
}

int solve_col(){
    // col is the same as row
    for(int i = 1; i <= M; ++i)can[i] = -1;
    for(int i = M; i >= 1; --i){
        if(~can[i])continue;
        if(M % i != 0)continue;
        for(int j = 2 * i; j <= M; j += i){
            if(M % j != 0)continue;
            vector<vector<int>> t;
            for(int k = 1; k <= j / i; ++k){
                int c1 = (k - 1) * i + 1;
                int r1 = 1;
                int c2 = k * i;
                int r2 = 1;
                t.push_back({r1 , c1 , r2 , c2});
            }
            if(check(t , 0 , t.size() - 1 , N , 0))can[i] = 1;
            else can[i] = 0;
            break;
        }
        if(can[i] == 0){
            for(int j = 1; j <= M; ++j){
                if(i % j == 0){
                    can[j] = 0;
                }
            }
        }
        else{
            can[i] = 1;
            for(int j = 1; j <= M; ++j){
                if(can[j] == 1){
                    int d = gcd(i , j);
                    for(int dd = d; dd <= M; dd += d){
                        if(M % dd == 0){
                            can[dd] = 1;
                        }
                    }
                }
            }
        }
    }
    int ret = 0;
    for(int i = 1; i <= M; ++i){
        if(can[i] == 1 && M % i == 0){
            ++ret;
        }
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    int ret = solve_row() * solve_col();
    cout << "! " << ret << endl;
    cout.flush();
}