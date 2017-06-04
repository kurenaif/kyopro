class MaxFlow {
	struct Edge {
		int to, cap, rev; 
		Edge(int t, int c, int r) :to(t), cap(c), rev(r){}
	};

public:

	vector<vector<Edge> > G;
	vector<bool > used;

	MaxFlow(int MAX_V) :G(MAX_V), used(MAX_V) {}

	void add_edge(int from, int to, int cap) {
		G[from].push_back(Edge(to,cap,G[to].size()));
		G[to].push_back(Edge(from, 0, G[from].size() - 1));
	}

	int dfs(int v,int t,int f) {
		if (v == t) return f;
		used[v] = true;
		for (int i = 0; i < G[v].size(); ++i) {
			Edge &e = G[v][i];
			if (!used[e.to] and e.cap>0) {
				int d = dfs(e.to, t, min(f, e.cap));
				if (d > 0) {
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	int max_flow(int s, int t) {
		int flow = 0;
		while (true) {
			fill(ALL(used), false);
			int f = dfs(s, t, 0x3f3f3f3f);
			if(f == 0) return flow;
			flow += f;
		}
	}
};