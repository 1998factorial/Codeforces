#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    int N = 3e5;
    for(int i = 1; i <= N; ++i){
        cout << rand() % N + 1 << " ";
    }
    cout << endl;
}
