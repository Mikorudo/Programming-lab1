#include "LargeArray.h"


LargeArray::LargeArray(long _size, std::string _filename) {
	if (_size < 0) {
		throw std::exception("Negative array size");
	}
	filename = _filename;
	size = _size;
	for (int i = 0; i < PagesInMemory; i++) {
		pages[i].lastAccessTime = time(NULL);
		pages[i].pageNum = i;
		pages[i].pageStatus = 0;
		for (int var : pages[i].valueArray)
			var = 0;
	}
	for (size_t i = 0; i < PagesInMemory; i++)
		bitMaps[i] = std::bitset<PageSize / 4>(0);

	filePtr = new std::fstream(filename, std::ios::binary | std::ios::in | std::ios::out | std::fstream::trunc);
	if (!filePtr) {
		throw std::exception("Couldn't open file");
	}
}
LargeArray::~LargeArray() {
	//savePages()
	if (filePtr != NULL)
		delete filePtr;
}
long LargeArray::GetArraySize() const {
	return size;
}
int* LargeArray::GetAddress(long index) {
	try {
		int pageNum = index / (PageSize / 4);
		bool isPageExist = false;
		int selectedPage = -1;
		for (size_t i = 0; i < PagesInMemory; i++) {
			if (pages[i].pageNum == pageNum) {
				isPageExist = true;
				selectedPage = i;
				break;
			}
		}
		if (!isPageExist) {
			int oldestPage = 0;
			for (int i = 0; i < PagesInMemory; i++) {
				if (pages[oldestPage].lastAccessTime < pages[i].lastAccessTime)
					oldestPage = i;
			}
			selectedPage = oldestPage;
			if (pages[selectedPage].pageStatus == 0) {
				SavePage(selectedPage);
			}
			pages[selectedPage] = LoadPage(pageNum);
			pages[selectedPage].lastAccessTime = time(NULL);
		}
		int relativeAddress = index % 128;
		int* absoluteAddress = &pages[selectedPage].valueArray[relativeAddress];
		return absoluteAddress;
	}
	catch (const std::exception&) {
		return nullptr;
	}

}

void LargeArray::SavePage(int selectedPage) {
	int bytes = selectedPage * (128 * sizeof(char) + 128 * sizeof(int));
	filePtr->seekp(bytes, std::ios_base::beg);
	std::string bitMap = PackBytes(selectedPage);
	filePtr->write((char*) &bitMap, 128);
	filePtr->write(reinterpret_cast<char*>(&pages->valueArray), sizeof(pages->valueArray));
	return;
	//for (size_t i = 0; i < 128; i++) {
	//	filePtr->write((char*) &pages->valueArray[i], sizeof(int));
	//}
}

Page LargeArray::LoadPage(int pageNum) {
	if (pageNum < 0)
		throw std::invalid_argument("Negative page number");
	int bytes = pageNum * (128 * sizeof(char) + 128 * sizeof(int));
	filePtr->seekg(bytes, std::ios_base::beg);
	int arr[128];
	for (size_t i = 0; i < 128; i++) {
		filePtr->read((char*) &/*!!!*/arr[i], sizeof(int));
	}
	Page page;
	page.lastAccessTime = time(NULL);
	page.pageNum = pageNum;
	page.pageStatus = 0;
	for (size_t i = 0; i < 128; i++) {
		page.valueArray[i] = arr[i];
	}
	return page;
}

std::string LargeArray::PackBytes(int selectedPage) {
	std::string str(128, char(00));
	for (size_t i = 0; i < 128; i++) {
		if (bitMaps[selectedPage][i] == 1) {
			str[i] = char(01);
		} else {
			str[i] = char(00);
		}
	}
	std::cout << str;
	return str;
}
int LargeArray::GetValue(long index, int& result) {
	try {
		int* absoluteAddress = GetAddress(index);
		result = *absoluteAddress;
	}
	catch (const std::exception&) {
		return 0;
	}
	return 1;
}
int LargeArray::SetValue(long index, int value) {
	try {
		int* absoluteAddress = GetAddress(index);
		*absoluteAddress = value;
		int pageNum = index / (PageSize / 4);
		int selectedPage = -1;
		bool isPageExist = false;
		for (size_t i = 0; i < PagesInMemory; i++) {
			if (pages[i].pageNum == pageNum) {
				isPageExist = true;
				selectedPage = i;
				break;
			}
		}
		if (!isPageExist)
			throw std::exception("!!!");
		bitMaps[selectedPage].set(index % 128);
	}
	catch (const std::exception&) {
		return 0;
	}
	return 1;
}