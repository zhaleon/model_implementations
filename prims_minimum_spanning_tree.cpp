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

int N, M;
vpi adj[200001];
bool tree[100001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

	cin >> N >> M;
	rep(i,1,M) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].emplace_back(b,c);
		adj[b].emplace_back(a,c);
	}

	int tree_size = 0;
   	priority_queue<pii, vpi, greater<pii>> pq;
	ll weight = 0;
	pq.push({0,1});
	while (tree_size < N && pq.size()) {
		pii cur = pq.top(); pq.pop();
		if (tree[cur.S]) continue;
		weight += cur.F;
		tree[cur.S] = 1;
		tree_size++;
			
		for (auto &edge : adj[cur.S]) {
			if (!tree[edge.F]) {
				pq.push(MP(edge.S,edge.F));
			}
		}

	}

	if (tree_size < N) {
		cout << "IMPOSSIBLE\n";
	} else {
		cout << weight << endl;
	}

    return 0;
}








