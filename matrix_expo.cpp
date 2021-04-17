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
#define rep(i,a,b) for (int i = a; i < b; i++)

void setIO(string name) {
	freopen((name+".in").c_str(), "r", stdin); 
	freopen((name+".out").c_str(), "w", stdout);
}

int N, M, K;

ll res[100][100];
ll adj[100][100];

template<size_t S> void mult(ll (&a)[S][S], ll(&b)[S][S]) {
	ll temp[S][S];
	memset(temp, 0x3f, sizeof(temp));

	rep(i,0,S)
		rep(j,0,S)
			rep(k,0,S)
				temp[i][j] = min(temp[i][j], a[i][k] + b[k][j]);

	rep(i,0,S)
		rep(j,0,S)
			a[i][j] = temp[i][j];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

	cin >> N >> M >> K;
   	
	memset(adj, 0x3f, sizeof(adj));
	memset(res, 0x3f, sizeof(res));	
	rep(i,0,100) res[i][i] = 0;
	
	rep(i,0,M) {
		ll a, b, w;
		cin >> a >> b >> w;
		a--, b--;
		adj[a][b] = min(adj[a][b], w);
	}

	while (K) {
		if (K & 1)
			mult<100>(res, adj);
		mult<100>(adj, adj);
		K >>= 1;
	}
	
	ll ans = res[0][N-1]; 

	if (ans > 1e18) 
		cout << -1 << endl;
	else
		cout << ans << endl;

    return 0;
}








