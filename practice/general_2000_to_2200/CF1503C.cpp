#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int a[maxn] , c[maxn] , N;

// dis(i -> j) = max(c[i] , a[j] - a[i])

// answer is at least c[1] + .. + c[N]

1 9
2 1
4 1




int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> N;
    vector<int> id;
    for(int i = 1; i <= N; ++i){
        cin >> a[i] >> c[i];
        id.push_back(i);
    }
    sort(id.begin() , id.end() , [&](int l , int r){
        return a[l] < a[r];
    });

}