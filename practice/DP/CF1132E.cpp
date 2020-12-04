/*
    Dynamic programming

    usual nacpsack
    DP[i][j] = select a subset of items from the first i category such that their sum is j
    but W is large
    LCM(1 , 2 ... , 8) = 840
    so let DP[i][j] = maximal number of bags has weight = 840 we can get from selecting
    a subset of items from the first i catergory where we are lefting out j amount of weight
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = 1e18 + 10;
ll cnt[10];
ll DP[10][840 * 10 + 10];
ll W;

int main(){
    cin >> W;
    for(int i = 1; i <= 8; ++i)cin >> cnt[i];
    for(int i = 0; i <= 8; ++i){
        for(int j = 0; j <= 840 * 10; ++j){
            DP[i][j] = -inf;
        }
    }
    DP[0][0] = 0;
    for(int i = 1; i <= 8; ++i){
        for(int j = 0; j <= 840 * 10; ++j){
            DP[i][j] = DP[i - 1][j];
            for(int k = 0; k <= min(840ll , cnt[i] * i); k += i){
                // we are lefting out amount of k at item i
                if(j - k < 0)break;
                DP[i][j] = max(DP[i][j] , DP[i - 1][j - k] + (cnt[i] * i - k) / 840ll);
            }
        }
    }
    ll ret = 0;
    for(int i = 0; i <= min(840ll * 10 , W); ++i){
        if(DP[8][i] < 0)continue;
        ret = max(ret , 840ll * min((W - i) / 840ll , DP[8][i]) + i);
        // excluding i , w can make at most (w - i) / 840 packs of 840
    }
    cout << ret << endl;
}
