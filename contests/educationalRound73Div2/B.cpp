#include <iostream>
using namespace std;

int main(){
  int n;
  cin >> n;
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      if(i % 2 == 0){
        if(j % 2 == 0){
          cout << "B";
        }
        else{
          cout << "W";
        }
      }
      else{
        if(j % 2 == 0){
          cout << "W";
        }
        else{
          cout << "B";
        }
      }
    }
    cout << endl;
  }
  return 0;
}
