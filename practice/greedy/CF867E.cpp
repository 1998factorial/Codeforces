#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N;
    vector<int> a(N);
    for(int i = 0; i < N; ++i){
        cin >> a[i];
    }
    multiset<int> candidates;
    ll ret = 0;
    for(int i = 0; i < N; ++i){
        if(candidates.empty()){
            candidates.insert(a[i]);
            continue;
        }
        if(*candidates.begin() >= a[i]){
            candidates.insert(a[i]);
            continue;
        }
        ret += a[i] - *candidates.begin();
        candidates.erase(candidates.begin());
        candidates.insert(a[i]); // as a buy
        candidates.insert(a[i]); // as an intermidate sell
    }
    cout << ret << endl;
}