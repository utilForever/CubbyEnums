#include "Fruit.hpp"

#include <iostream>

int main()
{
	Fruit fruit = StrToEnum<Fruit>("MANGO");
	std::cout << EnumToStr(fruit) << std::endl;

	fruit = Fruit::APPLE;
	std::cout << EnumToStr(fruit) << std::endl;
	
	return 0;
}