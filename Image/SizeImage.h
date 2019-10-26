#pragma once
#include <fstream>
#include <string>
using namespace std;

struct SizeImage {
	uint16_t widht;
	uint16_t height;
};

uint16_t byteToInt16(const char *byte, int begin) {
	uint16_t n;
	memcpy(&n, &byte[begin], sizeof(n));
	return n;
}

SizeImage getSizeImage(string pathfile) {
	SizeImage size;
	ifstream file(pathfile.c_str(), ios::binary);

	char buff[40];
	file.read(buff, 40);

	size.widht = byteToInt16(buff, 18);
	size.height = byteToInt16(buff, 22);

	cout << size.widht << endl;
	cout << size.height << endl;
	
	file.close();

	SizeImage a = { 1, 1 };
	return a;
}
