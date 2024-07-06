#include <iostream>

namespace FaragonEngine
{
	_declspec(dllimport) int Add(int, int);
}

void main()
{
	std::cout << FaragonEngine::Add(1, 2);
}