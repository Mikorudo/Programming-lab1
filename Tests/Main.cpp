#include <ctime>
#include <vector>

struct Page {
	char pageStatus; //0 Ц страница не модифицировалась, 1 Ц если была запись
	int pageNum;
	time_t lastAccessTime;
	int valueArray[128];
};

void SavePage() {
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

Page LoadPage() {
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

int main() {
	return 0;
}