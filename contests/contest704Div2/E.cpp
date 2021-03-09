#include <bits/stdc++.h>
using namespace std;
int N , M;

vector<int> getpos(vector<int> b , vector<int> c){
    vector<int> ret;
    for(int i = 0; i < b.size(); ++i){
        if(b[i] != c[i]){
            ret.push_back(i);
        }
    }
    return ret;
}

int cal(vector<int> b , vector<int> c){
    return (int)getpos(b , c).size();
}

void YES(vector<int> a){
    cout << "Yes" << endl;
    for(int i : a)cout << i << " ";
    cout << endl;
}

void NO(){
    cout << "No" << endl;
}

int main(){
    // goal is to construct an array x
    // such that max{hamming(x , a[i])} <= 2
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    vector<vector<int>> a = vector<vector<int>> (N , vector<int> (M));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cin >> a[i][j];
        }
    }
    int mx = 0;
    for(int i = 0; i < N; ++i)mx = max(mx , cal(a[0] , a[i]));
    if(mx <= 2){
        YES(a[0]);
        exit(0);
    }
    if(mx > 4){
        NO();
        exit(0);
    }
    if(mx == 4){
        // we need to find an array st hamming(a[0] , a[x]) == 4
        // and we change exactly 2 positions on a[0]
        int x = 0;
        vector<int> pos;
        for(int i = 0; i < N; ++i){
            pos = getpos(a[0] , a[i]);
            if(pos.size() == 4){
                x = i;
                break;
            }
        }
        // enumerating the possible 2 matches
        // at most 6 options
        for(int i = 0; i < 3; ++i){
            for(int j = i + 1; j < 4; ++j){
                vector<int> v = a[0];
                v[pos[i]] = a[x][pos[i]];
                v[pos[j]] = a[x][pos[j]];
                int ok = 1;
                for(int k = 0; k < N; ++k){
                    ok &= (cal(v , a[k]) <= 2);
                }
                if(ok){
                    YES(v);
                    exit(0);
                }
            }
        }
        NO();
        exit(0);
    }
    // now we are left with case with max{hamming(a[0] , a[i])} = 3
    int x = 0;
    vector<int> pos;
    for(int i = 0; i < N; ++i){
        pos = getpos(a[0] , a[i]);
        if(pos.size() == 3){
            x = i;
            break;
        }
    }
    // say we force 2 positions on a[0] to match a[x]
    for(int i = 0; i < 2; ++i){
        for(int j = i + 1; j < 3; ++j){
            vector<int> v = a[0];
            v[pos[i]] = a[x][pos[i]];
            v[pos[j]] = a[x][pos[j]];
            int ok = 1;
            for(int k = 0; k < N; ++k){
                ok &= (cal(v , a[k]) <= 2);
            }
            if(ok){
                YES(v);
                exit(0);
            }
        }
    }
    // now we try to match one position on a[0] with a[x]
    for(int i = 0; i < 3; ++i){
        vector<int> v = a[0];
        v[pos[i]] = a[x][pos[i]];
        int max_diff = 0 , y = -1;
        for(int j = 0; j < N; ++j){
            int dis = cal(v , a[j]);
            if(max_diff < dis){
                max_diff = dis;
                y = j;
            }
        }
        if(max_diff <= 2){
            YES(v);
            exit(0);
        }
        if(max_diff > 3){
            continue;
        }
        for(int j = 0; j < 3; ++j){
            if(i == j)continue; // since we fixed a[0][pos[i]]
            for(int k = 0; k < N; ++k){
                if(cal(v , a[k]) == 3){ // a bad one
                    if(v[pos[j]] != a[k][pos[j]]){ // make a[0][pos[j]] to a[k][pos[j]]
                        v[pos[j]] = a[k][pos[j]];
                        int ok = 1;
                        for(int t = 0; t < N; ++t){
                            ok &= (cal(v , a[t]) <= 2);
                        }
                        if(ok){
                            YES(v);
                            exit(0);
                        }
                        v[pos[j]] = a[0][pos[j]]; // restore
                    }
                    break; // one is enough as we need to make it good for everyone
                }
            }
        }
    }
    NO();
    exit(0);
}
