// @brief topological sort (Khan's algorithm O(|V|+|E|))
// @param G[node] = {to} (G: adjacency list)
// @return sorted values (if G is closed: {})
template<class T>
vector<T> tsort(const vector<vector<T> >& G) {
	vector<T> res;
	vector<T> in(G.size());
	for (auto &node : G) for (auto &to : node) ++in[to];

	queue<int> que;
	REP(i, in.size()) if (in[i] == 0) que.push(i);

	while (not que.empty()) {
		int n = que.front(); que.pop();
		res.push_back(n);
		for (auto &to : G[n]) if (--in[to] == 0) que.push(to);
	}
	return *max_element(ALL(in)) == 0 ? res : vector<T>();
}
