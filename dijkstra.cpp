#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pair<int, int> > vpi;

#define INF 1000000000
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define rep(i,a,b) for (int i = a; i <= b; i++)

int N, M, Q;

vpi adj[1001];
int fuel_cost[1001];
int dist[1001][100];

struct state {
    int cost, d, gas;
    
    state(int cost, int d, int gas) : cost(cost), d(d), gas(gas) {};
    
    bool operator<(const state &o) const {
        return cost > o.cost;
    }
};

void solve(int s, int e, int c) {
    memset(dist, 63, sizeof(dist));
    dist[s][0] = 0;
    
    priority_queue<state> pq;
    pq.emplace(0,s,0);
    
    int reps = 0;
    
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        
        if (dist[cur.d][cur.gas] < cur.cost) continue;
        
        for (auto &edge : adj[cur.d]) {
            
            if (edge.S <= cur.gas && cur.cost < dist[edge.F][cur.gas - edge.S]) {
                dist[edge.F][cur.gas - edge.S] = cur.cost;
                pq.emplace(cur.cost, edge.F, cur.gas - edge.S);
            }
            
        }
        
        if (cur.gas < c && cur.cost + fuel_cost[cur.d] < dist[cur.d][cur.gas + 1]) {
            dist[cur.d][cur.gas + 1] = cur.cost + fuel_cost[cur.d];
            pq.emplace(dist[cur.d][cur.gas + 1], cur.d, cur.gas + 1);
        }
        
    }
    
    int best = INF + 1;
    rep(i,0,c) best = min(best, dist[e][i]);
    
    if (best > INF) cout << "impossible\n";
    else cout << best << '\n';
    
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> N >> M;
    
    rep(i,1,N) cin >> fuel_cost[i];
    rep(i,1,M) {
        int a, b, w;
        cin >> a >> b >> w;
        ++a, ++ b;
        adj[a].emplace_back(b,w);
        adj[b].emplace_back(a,w);
    }

    cin >> Q;
    
    rep(i,1,Q) {
        int c, s, e;
        cin >> c >> s >> e;
        ++s, ++e;
        solve(s, e, c);
    }

    return 0;
}