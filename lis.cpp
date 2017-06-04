int LIS(const vector<int>& src) {
	vector<int> dp(src.size());
	fill(dp.begin(), dp.end(), 0x3f3f3f3f);

	REP(i, src.size()) {
		*lower_bound(dp.begin(), dp.end(), src[i]) = src[i];
	}
	return lower_bound(dp.begin(), dp.end(), 0x3f3f3f3f) - dp.begin();
}
