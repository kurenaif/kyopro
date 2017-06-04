
//n段のパスカルの三角形を生成 nCnの計算まで可能になる
//aCb = dst[a][b]
void pascalTriangle(int n, vector<vector<int> >* dst) {
	(*dst).resize(n+1);

	(*dst)[0].push_back(1);

	for (int i = 1; i <= n; ++i) {
		(*dst)[i].resize(i + 1);
		(*dst)[i][0] = 1;
		(*dst)[i][i] = 1;

		for (int j = 1; j < i; ++j) {
			(*dst)[i][j] = (*dst)[i - 1][j] + (*dst)[i - 1][j - 1];
		}
	}
}

//ベル数をnまで求める
void bellTriangle(int n, vector<int> *dst) {
	(*dst).resize(n + 1);
	vector<vector<int> > v;
	v.resize(n+1);
	v[0].push_back(1);//空集合は1
	(*dst)[0] = 1;
	v[1].push_back(1);
	(*dst)[1] = 1;

	for (int i = 2; i < v.size(); ++i) {
		v[i].resize(i);
		v[i][0] = v[i - 1].back();

		for (int j = 1; j < v[i].size(); ++j) {
			v[i][j] = v[i][j - 1] + v[i - 1][j - 1];
		}

		(*dst)[i] = v[i].back();
	}
}
