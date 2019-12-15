#include <iostream>
#include <cstdio>
#include <string>
#include <sstream> 
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cassert>
#include <iomanip>
using namespace std;
#define REP(i,a,b) for(int i=a;i<b;i++) 
/*

You are given a set of n
points in a 2D plane. No three points are collinear.
A pentagram is a set of 5 points, like a convex pentagon

count the number of convex pentagon
*/
//find all segments and sort them by angle
//let dp[i][j][k]=the number of clockwise tour from node i to node j has length k
//return dp[i][i][5],0<=i<n
typedef long long ll;
const int maxn=305;
ll dp[maxn][maxn][6];
int n,x[maxn],y[maxn];
vector<pair<double,pair<int,int>>>seg;
int main(){
	ios_base::sync_with_stdio(0);
	cin>>n;
	REP(i,0,n)cin>>x[i]>>y[i];
	REP(i,0,n){
		REP(j,0,n){
			REP(k,0,6)dp[i][j][k]=0;
			if(i==j)dp[i][j][0]=1;
		}
	}
	REP(i,0,n){
		REP(j,0,n){
			if(i!=j){
				int xx=x[j]-x[i],yy=y[j]-y[i];
				seg.push_back({atan2(xx,yy),{i,j}});
			}
		}
	}
	sort(seg.begin(),seg.end());//sort by angle
	int m=seg.size();
	REP(cc,0,m){
		int i=seg[cc].second.first,j=seg[cc].second.second;
		REP(k,0,n)
			REP(f,0,5)
				dp[k][i][f+1]+=dp[k][j][f];
	}
	ll ret=0;
	REP(i,0,n)ret+=dp[i][i][5];
	cout<<ret<<endl;
	return 0;
}