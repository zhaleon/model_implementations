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
    ios::sync_with_stdio(0); cin.tie(0);
}

int N, Q;
vi adj[100001];
int farm[100001];

int parent[100001];
bool active[100001];

int cur_chain = 0;
int cur_ind = 0;
int far, dist;

int chain[100001];
int chain_depth[100001];
int par_chain[100001];
int head[100001];

int ind[100001];

int bit[100001];


void upd(int pos, int delta) {
	while (pos < N+1) {
		bit[pos] ^= delta;
		pos += pos & -pos;
	}
}

int xor_query(int i) {
	int res = 0;
	while (i) {
		res ^= bit[i];
		i -= i & -i;
	}
	return res;
}

int xor_query(int i, int j) {
	if (i > j) swap(i,j); assert(i);
	return xor_query(j) ^ xor_query(i-1);
}

int find_far(int cur, int& ans, int p = 0, int cur_d = 1) { //find farthest in subtree
	parent[cur] = p;
	
	if (cur_d > dist)
		ans = cur, dist = cur_d;

	for (auto &edge : adj[cur]) 
		if (edge != p && active[edge])  
			find_far(edge, ans, cur, cur_d+1);	
	
	return ans;
}

int query(int a, int b) {
	int res = 0;

	if (chain_depth[a] < chain_depth[b]) swap(a, b);
	
	while (chain_depth[a] > chain_depth[b]) {
		res ^= xor_query(ind[a], ind[head[a]]);
		assert(chain_depth[a]-1 == chain_depth[par_chain[head[a]]]);
		a = par_chain[head[a]];
	}

	assert(chain_depth[a] == chain_depth[b]);
	
	while (chain[a] != chain[b]) {
		res ^= xor_query(ind[a], ind[head[a]]) ^ xor_query(ind[b], ind[head[b]]);
		a = par_chain[head[a]], b = par_chain[head[b]];
	} //somehow broken here
	
	res ^= xor_query(ind[a], ind[b]);
	return res;
}

int main() {
	setIO("cowland");
	
	cin >> N >> Q;
   	
	rep(i,1,N+1) cin >> farm[i];

	rep(i,0,N-1) {
		int a, b; cin >> a >> b;
		adj[a].PB(b);
		adj[b].PB(a);
	}
	
	memset(active, 1, sizeof(active));
	parent[0] = -1;

	queue<int> q; q.push(find_far(1,far));
	assert(q.front());

	while (q.size()) {
		dist = 0;
		int cur_head, tail;

		cur_head = q.front(), q.pop();
		tail = find_far(cur_head, far);

		++cur_chain;
		
		queue<int> nxt;
		
		while (~parent[tail]) {
			active[tail] = 0;
			chain[tail] = cur_chain;
			chain_depth[tail] = chain_depth[par_chain[cur_head]] + 1;

			ind[tail]= ++cur_ind;
			head[tail] = cur_head;

			nxt.push(tail);
			tail = parent[tail];
		}

		while (nxt.size()) {
			int cur = nxt.front();

			for (auto &edge : adj[cur]) 
				if (active[edge]) {
					par_chain[edge] = cur;
					chain_depth[edge] = chain_depth[cur] + 1;
					q.push(edge);
				}
			nxt.pop();
		}
	}
	
	rep(i,1,N+1) upd(ind[i], farm[i]);
	
	rep(i,0,Q) {
		int a, b, c;
		cin >> a >> b >> c;

		if (a == 1) {
			upd(ind[b], farm[b]);
			upd(ind[b], c);
			farm[b] = c;
		} else {
			cout << query(b, c) << endl;
		}
	}

    return 0;
}
