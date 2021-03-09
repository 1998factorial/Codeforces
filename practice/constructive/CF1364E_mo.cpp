#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int N;

int query(int i , int j){
    cout << "? " << i << " " << j << endl;
    cout.flush();
    int ret;
    cin >> ret;
    return ret;
}

void answer(vector<int> ans){
    cout << "! ";
    for(int i = 1; i <= N; ++i){
        cout << ans[i] << " ";
    }
    cout << endl;
    cout.flush();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    // goal is get where 0 is using at most 2222 querys
    // start with candidate a = p[1] and b = p[2] , we try to find where zero is 
    // if a | b < a | c => c is not zero (a , b) -> (a , b)
    // if a | b > a | c => b is not zero (a , b) -> (a , c)
    // if a | b = a | c => a is not zero (a , b) -> (c , b)
    vector<int> pos(N);
    for(int i = 1; i <= N; ++i)pos[i - 1] = i;
    shuffle(pos.begin() , pos.end() , rng);
    int a = pos[0] , b = pos[1] , v = query(a , b);
    for(int i = 2; i < N; ++i){
        int nv = query(a , pos[i]);
        if(v < nv){
            continue;
        }
        else if(v > nv){
            b = pos[i];
            v = nv;
        }
        else{
            a = pos[i];
            v = query(a , b); 
            // number of bits is decreased by at least one
            // guess this happens not many times, it is not easy for this to happen
        }
    }
    // we then need to choose either a or b 
    int pzero = -1;
    while(1){
        // again this will not happen many times
        // as each time, if v1 = v2 that means
        // c fully contains both a and b
        // and this does not happen too many times
        // given log2(2048) = 11
        int c = uniform_int_distribution<int>(1 , N)(rng);
        if(c == a || c == b)continue;
        int v1 = query(a , c);
        int v2 = query(b , c);
        if(v1 == v2)continue;
        pzero = (v1 < v2) ? a : b;
        break;
    }   
    // using where 0 is, we can get the rest of the array easily
    vector<int> ans(N + 1);
    for(int i = 1; i <= N; ++i){
        if(pzero == i)continue;
        ans[i] = query(i , pzero);
    }
    answer(ans);
}   