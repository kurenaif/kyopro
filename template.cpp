#include <iostream>
#include <queue>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <limits>
#include <cassert>
#include <fstream>
#include <cstring>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <ciso646>
#include <set>

using namespace std;

#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define RFOR(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define REP(i,n) for (int i=0;i<(n);i++)
#define RREP(i,n) for (int i=(n)-1;i>=0;i--)

#define inf 0x3f3f3f3f
#define INF INT_MAX/3
#define PB push_back
#define MP make_pair
#define ALL(a) (a).begin(),(a).end()
#define SET(a,c) memset(a,c,sizeof a)
#define CLR(a) memset(a,0,sizeof a)
#define pii pair<int,int>
#define pcc pair<char,char>
#define pic pair<int,char>
#define pci pair<char,int>
#define VS vector<string>
#define VI vector<int>
#define DEBUG(x) cout<<#x<<": "<<x<<endl
#define MIN(a,b) (a>b?b:a)
#define MAX(a,b) (a>b?a:b)
#define pi 2*acos(0.0)
#define INFILE() freopen("in0.txt","r",stdin)
#define OUTFILE()freopen("out0.txt","w",stdout)
#define ll long long
#define ull unsigned long long
#define eps 1e-14
#define FST first
#define SEC second
#define SETUP cin.tie(0), ios::sync_with_stdio(false), cout << setprecision(15)
struct input_returnner { 
	int N; input_returnner(int N_ = 0) :N(N_) {}
	template<typename T> operator vector<T>() const { vector<T> res(N); for (auto &a : res) cin >> a; return std::move(res); }
	template<typename T> operator T() const { T res; cin >> res; return res;} 
};
template<typename T> input_returnner in() { return in<T>(); }
input_returnner in() { return input_returnner(); }
input_returnner in(int N) { return std::move(input_returnner(N)); }

/// ---template---
void solve();

signed main(void) {
	SETUP;
	solve();
	return 0;
}

void solve() {
}
