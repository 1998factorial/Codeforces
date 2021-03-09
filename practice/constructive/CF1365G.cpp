#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N , Q = 13;

ll query(vector<int> q){
    cout << "? " << (int)q.size() << " ";
    for(int i : q){
        cout << i << " ";
    }
    cout << endl;
    cout.flush();
    ll ret;
    scanf("%lld" , &ret);
    return ret;
}

int main(){
    cin >> N;
    int cnt = 0;
    vector<int> ids;
    // goal is to construct a set of masks
    // such that no mask is a sub mask of another
    for(int mask = 0; mask < 1 << Q; ++mask){
        if(__builtin_popcount(mask) != Q / 2)continue;
        ids.push_back(mask);
        if(ids.size() >= N)break;
    }
    vector<vector<int>> qs;
    for(int i = 0; i < Q; ++i){
        // find all masks that contains ith bit
        vector<int> vec;
        for(int j = 0; j < N; ++j){
            if(ids[j] >> i & 1){
                vec.push_back(j + 1);
            }
        }
        qs.push_back(vec);
    }
    vector<ll> bits(Q) , ans(N);
    for(int i = 0; i < Q; ++i){
        if(qs[i].empty())continue;
        bits[i] = query(qs[i]); 
        // bits[i] = bitwise or of all indices whose id's mask contains 
        // the ith bit
    }
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < Q; ++j){
            if(ids[i] >> j & 1)continue;
            // answer[i] = bitwise or of all such that they contains at least one 
            // bit that is not in ids[i]
            ans[i] |= bits[j];
        }
    }
    cout << "! ";
    for(ll i : ans){
        cout << i << " ";
    }
    cout << endl;
    cout.flush();
}