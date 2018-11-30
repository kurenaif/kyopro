// dijkstra algorithm O((E+V)log V)
// G: adjacency list style Graph
//   G[node][pair<T, int>]: edges(cost, dst_node) start from node.
// start: start node
// goal: goal node(if this argument omitted, get all min distance from start node)
//
// usage: int dist = dijkstra(G,start,goal)[goal];
// usage: auto dist = dijkstra(G, start);
template<class T>
vector<T> dijkstra(const vector<vector<pair<T, int>> >& G, int start, int goal = -1) {
	using Ti = pair<T, int>;
	priority_queue<Ti, vector<Ti>, greater<Ti>> que;
	que.emplace(0, start);
	vector<T> dists(G.size(), inf);
	vector<int> prev(G.size(), -1);
	dists[start] = 0;

	while (not que.empty()) {
		int node, d; tie(d, node) = que.top();
		que.pop();
		if (dists[node] < d) continue;
		if (node == goal) {
			return dists;
		}
		for (const auto &edge : G[node]) {
			int nxt_node = edge.second;
			int next_dist = dists[node] + edge.first;
			if (dists[nxt_node] > next_dist) {
				dists[nxt_node] = next_dist;
				que.emplace(next_dist, nxt_node);
				prev[nxt_node] = node;
			}
		}
	}
	return dists;
}

// bellman ford algorithm O(EV)
// G: adjacency list style Graph
//   G[node][pair<T, int>]: edges(cost, dst_node) start from node.
// start: start node
// 
// note: if graph G has a negative cycle, return empty vector.
//
// usage: auto dist = bellman_ford(G, start);
template<class T>
vector<T> bellman_ford(const vector<vector<pair<T, int>>>& G, int start) {
	vector<T> dists(G.size(), inf);
	dists[start] = 0;
	vector<int> prev(G.size(), -1);

	REP(_, G.size() - 1) {
		REP(node, G.size()) {
			for (const auto &edge : G[node]) {
				int nxt_node = edge.second;
				int next_dist = dists[node] + edge.first;
				if (dists[nxt_node] > next_dist) {
					dists[nxt_node] = next_dist;
					prev[nxt_node] = node;
				}
			}
		}
	}

	REP(node, G.size()) {
		for (const auto &edge : G[node]) {
			int from = node;
			int to = edge.second;
			int cost = edge.first;
			if (dists[to] > dists[from] + cost) {
				return {};
			}
		}
	}

	return dists;
}

void draw_graph(const vector<vector<int> >& G) {
	ofstream fout("graph.dot");
	fout << "strict graph {";
	REP(i, G.size()) {
		REP(j, G[i].size()) {
			fout << i << "--" << G[i][j] << endl;
		}
	}
	fout << "}";
	fout.close();
	system("dot -Tpdf graph.dot -o graph.pdf");
	system("echo hello");
}
