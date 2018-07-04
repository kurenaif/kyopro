long long MaxRectInHist(const std::vector<int> &h) {
    int n = h.size();
    std::stack<int> s;
    std::vector<int> L(n), R(n);
    for (int i = 0; i < n; i++) {
        while (not s.empty() and h[s.top()] >= h[i]) s.pop();
        L[i] = s.size() ? (s.top() + 1) : 0;
        s.push(i);
    }
	s = stack<int>();
    for (int i = n - 1; i >= 0; i--) {
        while (not s.empty() && h[s.top()] >= h[i]) s.pop();
        R[i] = s.size() ? s.top() : n;
        s.push(i);
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res = std::max(res, (long long)(h[i]+1) * (R[i] - L[i]+1));
    }
    return res;
}

//Trueの部分の最大長方形の面積を求める
int GetMaxRect(vector<vector<bool> > field) {
	vector<vector<int> > hists(field.size(), vector<int>(field[0].size()));
	REP(j, field[0].size()) {
		if (field[0][j]) hists[0][j] = 1;
		else hists[0][j] = 0;
	}
	int res = MaxRectInHist(hists[0]);
	FOR(i, 1, field.size()) {
		REP(j, field[i].size()) {
			if (field[i][j] != 0) {
				hists[i][j] += hists[i - 1][j] + 1;
			}
		}
		res = max(res, MaxRectInHist(hists[i]));
	}
	return res;
}
