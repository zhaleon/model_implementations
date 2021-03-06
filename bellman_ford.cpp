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
ll dist[2501];

struct edge {
	ll a, b, w;
	edge() {};
	edge(ll a, ll b, ll w) : a(a), b(b), w(w) {};
};

edge edges[5001];
bool useful[5001];
bool v[5001];
bool v2[5001];

void search(int cur = N) {
	v[cur] = 1;
	rep(i,1,M)
		if (edges[i].b == cur && !v[edges[i].a])
			search(edges[i].a);
}

void search2(int cur = 1) {
	v2[cur] = 1;
	rep(i,1,M)
		if (edges[i].a == cur && !v2[edges[i].b])
			search2(edges[i].b);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> N >> M;
	rep(i,1,M) {
		ll a, b, w;
		cin >> a >> b >> w;
		edges[i] = edge(a,b,w);
	}

	search();
	search2();

	rep(i,1,M) 
		if (v[edges[i].a] && v[edges[i].b] && v2[edges[i].a])
			useful[i] = 1;

	rep(i,1,N) dist[i] = -1e18;
	dist[1] = 0;
	
	rep(i,1,N-1) {
		rep(j,1,M) {
			if (!useful[j]) continue;
			ll a = edges[j].a, b = edges[j].b, w = edges[j].w;
			if (dist[a] + w > dist[b])
				dist[b] = dist[a] + w;
		}
	}

	rep(j,1,M) {
		if (!useful[j]) continue;
		ll a = edges[j].a, b = edges[j].b, w = edges[j].w;
		if (dist[a] + w > dist[b]) {
			cout << -1 << endl;
			return 0;
		}
	}

	cout << dist[N] << endl;

    return 0;
}








