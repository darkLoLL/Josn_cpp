#include <iostream>

class pason {
public:
	pason(int i) {
		std::cout << "pason(int& i)" << std::endl;
	}
	pason(pason&& i) noexcept {
		std::cout << "pason(int&& i)" << std::endl;
	}
	pason(const pason& i) {
		std::cout << "pason(int& i)" << std::endl;
	}
	~pason()
	{
		std::cout << "~pason" << std::endl;
	}
};

pason fun() {
	int i = 12;
	pason son(i);
	return son;
}

int main() {
	int i;
	pason pa(fun());
	return 0;
}