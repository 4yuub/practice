#include <iostream>
#include <vector>
using namespace std;

template <typename IT, typename T>
int	bsearch(IT begin, IT end, T item) {
	int size = end - begin;
	IT initial_begin = begin;
	while (begin < end) {
		if (item > *(begin + size / 2)) {
			begin += size / 2 + 1;
		}
		else {
			end = begin + size / 2;
		}
		size = end - begin;
	}
	if (*begin == item)
		return begin - initial_begin;
	return -1;
}

int main(void) {
	vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
	cout << bsearch(v.begin(), v.end(), 8) << '\n';
	cout << bsearch(v.begin(), v.end(), 1) << '\n';
	cout << bsearch(v.begin(), v.end(), 5) << '\n';
	cout << bsearch(v.begin(), v.end(), 0) << '\n';

}
