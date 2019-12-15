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

int n,x;
bool v[1<<18];
//n<=18,1<=x<=2^18
//a[i+1]^a[0..i] => a[0..i]^a[0..i+1]=a[i+1]
//a[l..r]!=0 => a[i]!=a[j] & i!=j
//if a[i]^a[j]=x then we choose a[i] or a[j]
//
int main(){
	scanf("%d %d",&n,&x);
	v[0]=true;
	vector<int> b={0};
	//b[i]=a[0]^a[1]^...^a[i]
	for(int i=1;i<(1<<n);++i){
		//a[m]=i
		if(v[i^x])continue;
		//if we have choosen x^a[m] then we do not choose a[m]
		v[i]=true;
		b.push_back(i);
		//choose a[m] and mark a[m]^x
	}
	cout<<b.size()-1<<endl;
	for(int i=1;i<b.size();++i){
		printf("%d ",b[i]^b[i-1]);
	}
	return 0;
}