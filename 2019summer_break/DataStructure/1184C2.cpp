#include <iostream>
using namespace std;

const int maxn = 3e5 + 10;
int N , R;
struct point{
  int x , y;
  point(){}
  point(int x_ , int y_) : x(x_) , y(y_){}
} P[maxn];


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> R;
  for(int i = 1; i <= N; ++i){
    cin >> P[i].x >> P[i].y;
  }


}
