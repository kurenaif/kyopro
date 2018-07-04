#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <string>

using namespace std;

#define int long long

struct Edge {
	int to;
	int cost;
	int rev;
	Edge(int to, int cost, int rev) :to(to), cost(cost), rev(rev){}
	Edge(int to, int cost) :to(to), cost(cost), rev(-1){}
	Edge(int to) :to(to), cost(1), rev(-1){}
	Edge(){}
};

/**
 * DFS for Dinic
 * O(E)
 * @param level BFS result
 * @param Gf residual Graph
 * @param node start node
 * @param t target(goal) node
 * @param the amount of flowing
*/
int DinicDFS(const vector<int>& level,vector<vector<Edge>> &Gf, int node, int t, int flow = std::numeric_limits<int>::max()) {
	int res = 0;
	if (node == t) {
		return flow;
	}
	for (auto &e : Gf[node]) if(level[node] + 1 == level[e.to]){
		int f = DinicDFS(level, Gf, e.to, t, min(e.cost, flow));
		e.cost -= f;
		Gf[e.to][e.rev].cost += f;
		flow -= f;
		res += f;
		if (flow == 0) return res;
	}
	return res;
}

/**
 * Get Maximum Flow / Minimum Cut by Dinic Algorithm
 * O(V^2 E)
 * @param G Graph (not residual graph)
 * @param s start node
 * @param t target node
*/
int Dinic(const vector<vector<Edge> > &G, const int s, const int t) {
	int res = 0;
	vector<vector<Edge> > Gf(G.size());
	// construct Gf O(E)
	for (int i = 0; i < G.size(); ++i) {
		for (auto &e : G[i]) {
			int from = i;
			int to = e.to;
			int cost = e.cost;
			Gf[from].emplace_back(to, cost, Gf[to].size());
			Gf[to].emplace_back(from, 0, Gf[from].size()-1);
		}
	}

	// while loop: O(V^2 E)
	while (1) {
		// BFS(leveling) O(E)
		vector<int> level(G.size(), -1);
		queue<int> que;
		vector<vector<Edge*> > Gl;

		que.push(s);
		level[s] = 0;
		while (!que.empty()) {
			int from = que.front(); que.pop();
			for (auto &e : Gf[from]) {
				if (level[e.to] == -1 and e.cost > 0) {
					level[e.to] = level[from] + 1;
					que.push(e.to);
				}
			}
		}

		// O(E)
		if(level[t] == -1) return res;
		res += DinicDFS(level, Gf, s, t);
	}
	return 0;
}

signed main(void) {
	int N; cin >> N;
	vector<pair<int, int> > ab;
	vector<pair<int, int> > cd;
	
	vector<vector<Edge>> G(N * 2 + 2); // cost, to
	for (int i = 0; i < N; ++i) {
		int a, b; cin >> a >> b;
		ab.emplace_back(a, b);
	}
	for (int i = 0; i < N; ++i) {
		int c, d; cin >> c >> d;
		for (int j = 0; j < ab.size(); ++j) {
			if (ab[j].first < c && ab[j].second < d) {
				G[j].emplace_back(i+N, 1);
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		G[2 * N].emplace_back(i);
		G[i + N].emplace_back(2*N+1);
	}

	cout << Dinic(G, 2 * N, 2 * N + 1) << endl;
}

