#include <map>
#include <vector>
#include <iostream>

std::vector<int> get_primes_lt(const int &n) {
	std::map<int, bool> not_prime;

	not_prime[0] = true;
	not_prime[1] = true;
	for (int i = 0; i * i < n; i++) {
		if (!not_prime[i]) {
			for (int j = i * i; j < n; j += i) {
				not_prime[j] = true;
			}
		}
	}

	std::vector<int> ret;

	for (int i = 0; i < n; i++) {
		if (!not_prime[i]) {
			ret.push_back(i);
		}
	}
	return ret;
}

int main(void) {
	int n;
	std::cout << "primes less than: ";
	std::cin >> n;
	if (!std::cin.good()) {
		std::cerr << "Bad input\n";
		return 1;
	}

	std::vector<int> v = get_primes_lt(n);
	for (int &i : v)
		std::cout << i << '\n';
}
