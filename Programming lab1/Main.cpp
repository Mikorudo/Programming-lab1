#include <iostream>
#include "LargeArray.h"

void main() {
	LargeArray largeArray(10000, "test.bm");
	largeArray.SetValue(10, 10);
	largeArray.SetValue(200, 200);
	largeArray.SetValue(400, 400);
	largeArray.SetValue(500, 500);

	int temp;
	largeArray.GetValue(10, temp);
	std::cout << temp << "\t";
	largeArray.GetValue(200, temp);
	std::cout << temp << "\t";
	largeArray.GetValue(400, temp);
	std::cout << temp << "\t";
	largeArray.GetValue(500, temp);
	std::cout << temp << "\t";
}
//Запись в файл
//Битовая карта в Get Set
//Записать bitMap в файл (через char)