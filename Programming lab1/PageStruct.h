#pragma once
#include <ctime>
#include <vector>

struct Page {
	char pageStatus; //0 � �������� �� ����������������, 1 � ���� ���� ������
	int pageNum;
	time_t lastAccessTime;
	int valueArray[128];
};