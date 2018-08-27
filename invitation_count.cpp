// count invitation. O(NlogN)
template<class T>
int invitation_count(vector<T> &a) {
	int count = 0;
	int n = a.size();
	if (n > 1) {
		vector<T> b(a.begin(), a.begin() + n / 2);
		vector<T> c(a.begin() + n / 2, a.end());
		count += invitation_count(b);
		count += invitation_count(c);

		for (int i = 0, j = 0, k = 0; i < n; ++i)
			if (k == c.size()) a[i] = b[j++];
			else if (j == b.size()) a[i] = c[k++];
			// invitation_count: i < j and a_i  > a_j
			// this case:        j < k and b[j] > c[k]
			else if (b[j] > c[k]) {
				a[i] = c[k++];
				count += n / 2 - j;
			}
			else {
				a[i] = b[j++];
			}
	}
	return count;
}
