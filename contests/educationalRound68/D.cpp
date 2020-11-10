/*
    Game , pattern finding

    After trying to print multiple caes, we find that when K does not contain any factor of 3,
    then Alice's losing state will be N = 3m
    If K = 3p, then we should observe a pattern of 3...3 (p - 1 3s) 4, note that these are the
    differences between losing[i] and losing[i - 1].
    and we should observe that N has something to do with (K + 1) in this case.
    it turns out that if N % (K + 1) == 0 (mod 3) and N % (K + 1) != K then Alice will lose
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        int N , K; cin >> N >> K;
        /*
        vector<int> DP(N + 1);
        vector<int> loses;
        for(int i = 1; i <= N; ++i){
            if(i - 1 >= 0)DP[i] |= !DP[i - 1];
            if(i - 2 >= 0)DP[i] |= !DP[i - 2];
            if(i - K >= 0)DP[i] |= !DP[i - K];
            //printf("DP[%d] = %d\n" , i , DP[i]);
            if(DP[i] == 0)loses.push_back(i - 1);
        }*/
        //if(DP[N])cout << "Alice" << endl;
        //else cout << "Bob" << endl;
        //cout << "losing state : " << endl;
        //for(int i : loses)cout << i << endl;
        //cout << "diff : " << endl;
        //for(int i = 1; i < loses.size(); ++i){
        //    cout << loses[i] - loses[i - 1] << endl;
        //}
        if(K % 3 != 0){
            if(N % 3 == 0){
                cout << "Bob" << endl;
            }
            else{
                cout << "Alice" << endl;
            }
        }
        else{
            int x = N % (K + 1);
            if(x % 3 == 0 && x != K){
                cout << "Bob" << endl;
            }
            else{
                cout << "Alice" << endl;
            }
        }
    }
}
