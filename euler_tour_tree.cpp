#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <assert.h>
#include <string>
#include <cstring>
#include <unordered_map>
#include <bitset>
#include <climits>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <deque>
#include <cmath>
#include <set>
#include <unordered_set>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<int> > vii;
typedef vector<int> vi;
typedef vector<pair<int, int> > vpi;

#define INF 1000000000
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define rep(i,a,b) for (int i = a; i < b; i++)

void setIO(string name) {
	freopen((name+".in").c_str(), "r", stdin); 
	freopen((name+".out").c_str(), "w", stdout);
}

int N, Q;
vi adj[100001];

int farm[100001];

int bit[200001];
int fir[100001];
int last[100001];

int parent[100001][19];
int depth[100001];

void upd(int pos, int delta, int size = 2*N+1) {
	while (pos < size) {
		bit[pos] ^= delta;
		pos += pos & -pos;
	}
}

int sum(int i) {
	int res = 0;
	while (i > 0) {
		res ^= bit[i];
		i -= i & -i;	
	}
	return res;
}

int t = 1;
void dfs(int cur) {
	fir[cur] = t++;
	for (auto edge : adj[cur]) if (!fir[edge]) dfs(edge);
	last[cur] = t++;
}

void lcaPre(int cur, int d) {
	depth[cur] = d;
	for (auto edge : adj[cur]) {
		if (!parent[edge][0]) {
			parent[edge][0] = cur;
			lcaPre(edge, d+1);
		}
	}
}

int lca(int a, int b) {
	if (a == b) return a;
	if (depth[a] < depth[b]) swap(a, b);
	
	int dif = depth[a] - depth[b];
	int jump = 0;
	
	while (dif) {
		if (dif & 1) a = parent[a][jump];
		jump++;
		dif >>= 1;
	}
	
	if (a == b) return a;
	
	int p = 17;
	while (a != b && p--) {
		if (depth[a] > (1 << p) && parent[a][p] != parent[b][p]) {
			a = parent[a][p];
			b = parent[b][p];
		}
	}
	
	return parent[a][0];
}

int main() {
	setIO("cowland");
    ios::sync_with_stdio(0); cin.tie(0);

	cin >> N >> Q;

	rep(i,1,N+1) cin >> farm[i];

	int a, b, c;
	rep(i,0,N-1) {
		cin >> a >> b;
		adj[a].PB(b);
		adj[b].PB(a);
	}

	parent[1][0] = 1;
	lcaPre(1,1);
	dfs(1);	

	rep(i,0,17) {
		rep(j,1,N+1) {
			parent[j][i+1] = parent[parent[j][i]][i]; 
		}
	}
	
	rep(i,1,N+1) {
		upd(fir[i], farm[i]);
		upd(last[i], farm[i]);
	}
	rep(i,0,Q) {
		cin >> a >> b >> c;
		if (a  == 1) {
			upd(fir[b], farm[b]);
			upd(last[b], farm[b]);
			upd(fir[b], c);
			upd(last[b], c);
			farm[b] = c;
		} else {
			int _lca = lca(b,c);
			int ans = sum(fir[b]) ^ sum(fir[c]) ^ farm[_lca]; 
			cout << ans << endl;
		}
	}
    return 0;
}








