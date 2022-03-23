#include <iostream>
using namespace std;

class Base
{
    public:
        Base() {}
        ~Base() {}
};

class A: public Base {
    public:
        A() {}
        ~A() {}
};

class B: public Base {
    public:
        B() {}
        ~B() {}
};

int main() {
    double a = 2.1;
    // c style:
    double b = (int) a + 1.1;
    // c++ style:
    double c = static_cast<int>(a) + 1.1;

    cout << b << " | " << c << endl;

    A *obj_a = new A();
    Base *base = obj_a;

    A *ac = dynamic_cast<A*>(base);

    std::cout << base << std::endl;
}