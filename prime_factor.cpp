class prime {
private:
public:
	std::vector<int> primes;
	std::vector<bool> isPrime;
	prime(int num = 0) {
		if (num == 0) return;
		isPrime.resize(num + 1);
		fill(isPrime.begin(), isPrime.end(), true);
		int ma = sqrt(num) + 1;
		isPrime[0] = isPrime[1] = false;
		int cnt = 0;
		for (int i = 2; i <= ma; ++i) if (isPrime[i]) {
			for (int j = 2; i*j <= num; ++j) {
				isPrime[i*j] = false;
				cnt++;
			}
		}
		primes.reserve(cnt);
		for (int i = 0; i<isPrime.size(); ++i) if (isPrime[i]) {
			primes.push_back(i);
		}
	}

	bool IsPrime(int num) {
		if (num < isPrime.size()) return isPrime[num];
		for (auto p : primes) {
			if (num%p == 0) return false;
		}
		int ma = sqrt(num) + 1;
		for (int i = primes.back(); i <= ma; i += 2) {
			if (num%i == 0) return false;
		}
		return true;
	}

	std::map<int, int> GetFactor(int num) {
		std::map<int, int> res;
		int ma = sqrt(num) + 1;
		int a = 2;
		auto it = primes.begin();
		while (num >= a*a) {
			if (num%a == 0) {
				res[a]++;
				num /= a;
			}
			else {
				if (it == primes.end()) ++a;
				else {
					++it;
					a = *it;
				}
			}
		}
		res[num]++;
		return res;
	}
};

