#include <iostream>

class Int {
	public:
		int m_n;
	
		Int() {
			m_n = 0;
		}

		Int(int n) {
			m_n = n;
		}

		float operator/(const Int & rhs) {
			return (float) m_n / rhs.m_n;
		}
		
		Int operator&(const Int & rhs) {
			return m_n / rhs.m_n;
		}
		
		Int operator*(const Int & rhs) {
			return m_n * rhs.m_n;
		}
		
		Int operator+(const Int & rhs) {
			return m_n + rhs.m_n;
		}
		
		Int operator-(const Int & rhs) {
			return m_n - rhs.m_n;
		}

};

std::ostream & operator<<(std::ostream & o, Int const & rhs) {
	o << rhs.m_n;
	return o;
}

int main(void) {
	Int n = 1;
	Int n2 = 2;

	std::cout << n << " / " << n2 << ": " << n / n2 << "\n";
	std::cout << n << " * " << n2 << ": " << n * n2 << "\n";
	std::cout << n << " + " << n2 << ": " << n + n2 << "\n";
	std::cout << n << " - " << n2 << ": " << n - n2 << "\n";
}
