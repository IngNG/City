/*!
\file
\brief ������� ��� ������ �� `string`
*/
#pragma once
#include <string>
#include <vector>
using namespace std;

/*!
����� ������ �� �����������
\param[out] str ������ ��� ����������
\param[out] delim ��������
\param[in] output ������ ��� ���������� �������
\param[in] maxCountOutput ������ ������� `output`
\return ���-�� ����������� ���������
*/
vector<string> stringSplit(string str, string delim, int max=0) {
	int pos = 0;
	int i = 0;

	vector<string> result;

	while ((pos = str.find(delim)) != std::string::npos && (i != max | i == 0)) {
		string buff = str.substr(0, pos);
		result.push_back(buff);
		str.erase(0, pos + delim.length());
		i++;
	}

	if (i != max | i == 0) {
		result.push_back(str);
		i++;
	}

	return result;
}
