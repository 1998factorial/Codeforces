/*
    statement: we need to guess p[1]...p[N] , p[i] in [0,N-1]
    - each time we can ask the value of p[i] | p[j] , i != j
    - we are allowed to ask at most 4269 queries
    - N <= 2048 = 2^11

    Second solution

    goal is still to get the index where p[index] = 0
    here is an interesting way to express p[i].
    let z[i] = j => (p[j] >> i) & 1 = 0
    p[i] = query(i , z[0]) & query(i , z[1]) & ... & query(i , z[10])
    another observation is: if x | y = x , then y is a subset of x  
    uing these 2 observations, we can find the index of zero asking linear
    number of queries.
    at the end, we just need to assign query(i , index) to ans[i]
    2048 * 2 used for these 2 steps.

    Now how do we handle z[0...10] using at most 173 queries?
    we randomly select 2 indices i , j
    the chance that query(i , j) does not contain the kth bit is ~ 1/2
    on average, we should expect to have 2 queries per bit
    making it about 2 * 11. (I am not sure here, but I guess this is it)
*/
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

int count(vector<int> z){
    int ret = 0;
    for(int i : z){
        if(i == 0){
            ++ret;
        }
    }
    return ret;
}

int getp(int i , vector<int> z){ // return the interesting expression for p[i]
    int ret = (1 << 11) - 1;
    for(int j = 0; j < 11; ++j){
        if(z[j] != i){
            ret &= query(i , z[j]);
        }
        else if((ret >> j) & 1){
            ret ^= (1 << j);
        }
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    vector<int> z(11);
    while(count(z) > 0){
        // here we ask not many quries
        int i = uniform_int_distribution<int>(1 , N)(rng);
        int j = uniform_int_distribution<int>(1 , N)(rng);
        if(i == j)continue;
        int v = query(i , j);
        for(int k = 0; k < 11; ++k){
            if(!((v >> k) & 1)){
                z[k] = i;
            }
        }
    }
    int zpos = 1 , val = getp(1 , z);
    for(int i = 2; i <= N; ++i){ // we ask at most 2048 + 11 * 11 queris here
        int v = query(zpos , i);
        if(v == val){ // we know p[i] is subset of p[zpos]
            zpos = i;
            val = getp(zpos , z);
        }
    }
    vector<int> ans(N + 1);
    for(int i = 1; i <= N; ++i){
        if(i != zpos){
            ans[i] = query(i , zpos);
        }
    }
    answer(ans);
}