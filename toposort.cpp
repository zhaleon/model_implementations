#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<int>> vii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vpi;

#define INF 1000000000
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define rep(i,a,b) for (int i = a; i <= b; i++)

void setIO(string name) {
	freopen((name+".in").c_str(), "r", stdin); 
	freopen((name+".out").c_str(), "w", stdout);
}

int N, M, mod = 1e9+7;
vi adj[100001];
vi topo;
bool v[100001];

ll ways[100001];

void dfs(int cur) {
	v[cur] = 1;
	for (auto &edge : adj[cur]) 
		if (!v[edge])
			dfs(edge);
	
	topo.PB(cur);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

	cin >> N >> M;
	rep(i,1,M) {
		int a, b;
		cin >> a >> b;
		adj[a].PB(b);
	}

	rep(i,1,N) 
		if (!v[i])
			dfs(i);
  
	reverse(topo.begin(), topo.end());

	ways[1] = 1;
	for (auto &v : topo) 
		for (auto &edge : adj[v]) 
			(ways[edge] += ways[v]) %= mod;
	
	cout << ways[N] << endl;
	

    return 0;
}








