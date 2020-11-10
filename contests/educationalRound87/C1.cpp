#include <bits/stdc++.h>
using namespace std;

int main() {
    int t, n;
    scanf("%d" , &t);
    while(t--){
        scanf("%d" , &n);
        n *= 2;
        double angle = 3.14159265358979323846 / n;
        double len = 0.5 / tan(angle);
        printf("%.20lf\n" , len * 2);
    }
}
