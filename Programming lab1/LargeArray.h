#pragma once
#define PageSize 512
#define PagesInMemory 5
#include "PageStruct.h"
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <bitset>

class LargeArray {
public:
	LargeArray(long _size, std::string _filename);
	int* GetAddress(long index);
	int GetValue(long index, int& result);
	int SetValue(long index, int value);
	long GetArraySize() const;
	/*Переопределение []*/
	~LargeArray();
private:
	std::string filename;
	long size;
	std::fstream* filePtr;
	Page pages[PagesInMemory];
	std::bitset<PageSize / 4> bitMaps[PagesInMemory];
	std::string PackBytes(int selectedPage);
	void SavePage(int selectedPage);
	Page LoadPage(int pageNum);
};

/* std::ios::app - возможная ошибка*/
//Модификация страницы
