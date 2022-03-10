#pragma once
#include <ctime>
#include <vector>

struct Page {
	char pageStatus; //0 Ц страница не модифицировалась, 1 Ц если была запись
	int pageNum;
	time_t lastAccessTime;
	int valueArray[128];
};