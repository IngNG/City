#pragma once
#include <fstream>
#include <string>
using namespace std;

string readAllFile(string path) {
	ifstream file;
	file.open(path);

	string line;
	string result = "";
	while (getline(file, line)) {
		result += line + "\n";
	}
	file.close();
	return result;
}
