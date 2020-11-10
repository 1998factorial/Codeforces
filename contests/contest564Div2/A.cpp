#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <complex>
//#include <unordered_set>
#define REP(i,a,b) for(int i=a;i<b;i++)
#define RREP(i,a,b) for(int i=a;i>=b;i--)
#define FILL(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
int main(){
	int x,y,z;
	while(~scanf("%d %d %d",&x,&y,&z)){
		int mi=x-y-z,mx=x-y+z;
		if(mi==0&&mx==0)
			cout<<"0";
		else if(mi>0&&mx>0)
			cout<<"+";
		else if(mi<0&&mx<0)
			cout<<"-";
		else
			cout<<"?";
	}
	return 0;
}