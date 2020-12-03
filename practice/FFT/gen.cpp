#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9;
int main(){
    srand(time(NULL));
    int t = 1;
    int N = 5e5;
    printf("%d\n" , t);
    printf("%d\n" , N);
    for(int i = 1; i <= N; ++i){
        int v = rand() % 3;
        if(v == 0)cout << 'K';
        if(v == 1)cout << 'V';
        if(v == 2)cout << '?';
    }
    cout << endl;
}