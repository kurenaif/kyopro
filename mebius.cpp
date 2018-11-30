// Usage: Mebius mebius(N, Prime(N));
class Mebius {
public:
	vector<int> values;
	Mebius(int num, const Prime& prime): values(num+1, 1) {
		for (auto &p : prime.primes) {
			for (int i = p; i < num; i += p) {
				values[i] *= -1;
			}
			int p2 = p * p;
			for (int i = p2; i < num; i += p2) {
				values[i] = 0;
			}
		}
	}
};
