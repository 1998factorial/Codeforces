#include <bits/stdc++.h>
using namespace std;

int main(){
    int N; 
    int ans = 0;
    cin >> N;
    vector<int> p(N);
    vector<int> cnt(N);
    vector<vector<int>> ret;
    for(int i = 0; i < N; ++i)p[i] = i;
    do{
        vector<int> ip(N);
        for(int i = 0; i < N; ++i){
            ip[p[i]] = i;
        }
        int ok = 1;
        vector<vector<int>> vec;
        vector<bool> used(N);
        for(int i = 0; i < N; ++i){
            if(used[i])continue;
            vector<int> cur;
            int c = p[i];
            for(;;){
                if(used[c])break;
                used[c] = 1;
                cur.push_back(c);
                c = p[c];
            }
            sort(cur.begin() , cur.end() , [&](int l , int r){
                return ip[l] < ip[r];
            });
            int mx = -1 , id = -1;
            for(int j = 0; j < cur.size(); ++j){
                if(mx < cur[j]){
                    mx = cur[j];
                    id = j;
                }
            }
            vector<int> tmp(cur.size());
            for(int j = 0; j < cur.size(); ++j){
                tmp[(j - id + cur.size()) % cur.size()] = cur[j];
            }
            vec.push_back(tmp);
        }
        sort(vec.begin() , vec.end() , [&](vector<int>& l , vector<int>& r){
            return l[0] < r[0];
        });
        vector<int> np;
        for(vector<int>& v : vec){
            for(int i : v){
                np.push_back(i);
            }
        }
        for(int i = 0; i < N; ++i){
            ok &= np[i] == p[i];
        }
        if(ok){
            ret.push_back(p);
            ++ans;
            ++cnt[p[0]];
            for(int x : p){
                cout << x + 1 << " ";
            }
            cout << endl;
        }
    }while(next_permutation(p.begin() , p.end()));
    printf("ans = %d\n" , ans);
    for(vector<int>& a : ret){
        for(int j : a)cout << j + 1 << " ";
        cout << endl;
    }
}