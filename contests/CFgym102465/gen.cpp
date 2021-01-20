#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int N = 5;
    cout << N << endl;
    for(int i = 1; i <= N; ++i){
        int x = rand() % N , y = rand() % N;
        cout << min(x , y) << " " << max(x , y) << endl;
        //cout << 0 << " " << N - 1 << endl;
    }
}