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

int N, Q;
int nxt[200001];
vi adj[200001];
vi children[200001];

int depth[200001];
int parent[200001];
int id[200001];       //component id
int cycle_id[200001];
int tree_id[200001];
int tin[200001];
int tout[200001];
int root[200001];
int v[200001];
int fir[100001];
int las[100001];
int spot[200001]; //flatten out cycles
// map vertex -> location in array

bool in_cycle[200001];
bool has_cycle = 0;

void search(int cur, int num, queue<int> &q) {

	int start;
	while (true) {
		
		/* cout << "test " << cur << ' ' << ' ' << nxt[cur] << ' ' <<  num << endl; */
		
		if (v[nxt[cur]]) {
			if (v[nxt[cur]] == num) {
				parent[nxt[cur]] = cur;
				v[cur] = num;
				start = cur = nxt[cur];
				has_cycle = 1;
			}
			break;  
		} 
		
		v[cur] = num;
		parent[nxt[cur]] = cur;			
		cur = nxt[cur];	
	}
	
	/* cout << "WORKS? " << has_cycle << endl; */
	
	if (!has_cycle) {
		return;
	}

 	do {
		q.push(cur);
		cur = nxt[cur];
		in_cycle[cur] = 1;
	} while (cur != start);

}

void dfs(int cur, int d, int tree_root, const int& tree) {
	depth[cur] = d;
	tree_id[cur] = tree;
	root[cur] = tree_root;
	static int t = 0;

	tin[cur] = ++t;
	for (auto &child : children[cur]) 
		if (!in_cycle[child])
			dfs(child, d+1, tree_root, tree);
	tout[cur] = t;
}

void flood(int cur, int &color) {
	id[cur] = color;
	for (auto &edge : adj[cur]) 
		if (!id[edge])
			flood(edge, color);
}

void init() {
	int cur_color = 0;
	int cur_cycle = 0;
	int cur_tree = 0;
	int cur_index = 0;
	int num = 0;
	rep(i,1,N) 
		if (!id[i]) 
			flood(i, ++cur_color);
	
	rep(i,1,N) { 
		if (!v[i]) {
			has_cycle = 0;
			queue<int> q;
			
			search(i, ++num, q);
		
			if (!has_cycle)
				continue;

			++cur_cycle;
			fir[cur_cycle] = cur_index + 1;
			las[cur_cycle] = cur_index + q.size();

			while (!q.empty()) {
				int cur = q.front(); q.pop();
				cycle_id[cur] = cur_cycle;
				spot[cur] = ++cur_index;
				dfs(cur, 0, cur, ++cur_tree);
			}
		}
	}
}

bool is_ancestor(int a, int b) {
	return tin[a] < tin[b] && tout[b] <= tout[a];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> N >> Q;
	
	rep(i,1,N) { 
		cin >> nxt[i];
		adj[nxt[i]].PB(i);
		adj[i].PB(nxt[i]);
		children[nxt[i]].PB(i);
	}
	
	init();

	/* printf("in cycle?\n"); */
	/* rep(i,1,N) printf("%i: %i\n", i, in_cycle[i]); */
	/* printf("\n"); */	

	/* printf("cycle number\n"); */
	/* rep(i,1,N) printf("%i: %i\n", i, cycle_id[i]); */
	/* printf("\n"); */	
	
	/* printf("tree id\n"); */
	/* rep(i,1,N) printf("%i: %i\n", i, tree_id[i]); */
	/* printf("\n"); */	
	
	/* printf("tree root\n"); */
	/* rep(i,1,N) printf("%i: %i\n", i, root[i]); */
	/* printf("\n"); */	

	/* printf("connected component\n"); */
	/* rep(i,1,N) printf("%i: %i\n", i, id[i]); */
	/* printf("\n"); */	
	
	/* printf("\n\n"); */

	rep(i,1,Q) {
		int a, b;
		cin >> a >> b;
		
		if (a == b) {
			cout << 0 << endl;
		} else if (id[a] != id[b] || (!in_cycle[b] && in_cycle[a])) {
			//different connected components, start is in cycle, destination in tree
			cout << -1 << endl;
		} else if (!in_cycle[a] && in_cycle[b]) {
			//start is in tree, destination in cycle
			int res = 0;
			res += depth[a];
			a = root[a];
			int cycle_num = cycle_id[a];
		
			int len = 1 + abs(fir[cycle_num] - las[cycle_num]);
			
			cout << res + (spot[b]-spot[a]+len)%len << endl;  
		
		} else if (in_cycle[a] && in_cycle[b]) {
			//both in cycle
			int cycle_num = cycle_id[a];
		
			int len = 1 + abs(fir[cycle_num] - las[cycle_num]);
		
			cout << (spot[b]-spot[a]+len)%len << endl;

		} else if (!in_cycle[a] && !in_cycle[b] && tree_id[a] == tree_id[b]) {
			//neither in cycle, both in same tree
		
			if (!is_ancestor(b, a)) {
				cout << -1 << endl;
			} else {
				cout << abs(depth[b]-depth[a]) << endl;
			}

		} else {
			cout << -1 << endl;
		}
	}
    return 0;
}
