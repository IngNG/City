#pragma once
#include "../utils/FunString.h"
#include "../WindowObject/Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TXLib.h"
#include <Windows.h>

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

vector<int> ParseAreaCoord(string str) {
	vector<string> coordStr = stringSplit(str, "|");
	vector<int> coord;

	for (int i = 0; i < coordStr.size(); i++) {
		coord.push_back(atoi(coordStr[i].c_str()));
	}

	return coord;
}

Image parseObject(string str) {
	Image img;
	vector<string> lines = stringSplit(str, "\n");
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i] == "") {
			continue;
		}

		vector<string> strSplited = stringSplit(lines[i], "=", 2);
		string id = strSplited[0];
		string value = strSplited[1];

		if (id == "path") {
			img.adress = value;
		}
		else if (id == "widht") {
			img.widht = atoi(value.c_str());
		}
		else if (id == "height") {
			img.height = atoi(value.c_str());
		}
		else if (id == "coord") {
			vector<int> coord = ParseAreaCoord(value);
			img.area.x = coord[0];
			img.area.y = coord[1];
			img.area.widht = coord[2];
			img.area.height = coord[3];
		}
	}

	return img;
}

vector<Image> readSaveFile(string path, Image* menu, int sizeMenu) {
	vector<string> arrObjStr = stringSplit(readAllFile(path), "--OBJ--\n");
	vector<Image> arrObj;

	// Это нужно для Code::Blocks без этого не работает
	// Почему?
	// А * знает
	for (int qwe = 0; false; qwe++) {}

	for (int i = 0; i < arrObjStr.size(); i++) {
		if (arrObjStr[i] == "") {
			continue;
		}

		Image loadedObj = parseObject(arrObjStr[i]);
		// Инитиализуем изображение
		for (int j = 0; j < sizeMenu; j++) {
			if (loadedObj.adress == menu[j].adress) {
				loadedObj.img = menu[j].img;
				loadedObj.category = menu[j].category;
			}
		}
		arrObj.push_back(loadedObj);
	}

	return arrObj;
}

inline int GetFilePointer(HANDLE FileHandle)
{
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}


void SaveGameInFile(string nameFile, vector<Image> &objs) {

	ofstream file;
	file.open(nameFile);

	for (int i = 0; i < objs.size(); i++) {
		Image &obj = objs[i];
		file << "--OBJ--\n";
		file << "path=" << obj.adress + "\n";
		file << "widht=" << obj.widht << "\n";
		file << "height=" << obj.height << "\n";
		file << "coord=" << obj.area.x << "|" << obj.area.y << "|" << obj.area.widht << "|" << obj.area.height << "\n";
	}

	file.close();
}

bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height)
{
    bool Success=0;
    HBITMAP OffscrBmp=NULL;
    HDC OffscrDC=NULL;
    LPBITMAPINFO lpbi=NULL;
    LPVOID lpvBits=NULL;
    HANDLE BmpFile=INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;
    if ((OffscrBmp = Win32::CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
        return 0;
    if ((OffscrDC = Win32::CreateCompatibleDC(bitmapDC)) == NULL)
        return 0;
    HBITMAP OldBmp = (HBITMAP)Win32::SelectObject(OffscrDC, OffscrBmp);
    Win32::BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
    if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
        return 0;
    ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
    lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    Win32::SelectObject(OffscrDC, OldBmp);
    if (!Win32::GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
        return 0;
    if (!Win32::GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((BmpFile = CreateFile(filename,
                        GENERIC_WRITE,
                        0, NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL)) == INVALID_HANDLE_VALUE)
        return 0;
    DWORD Written;
    bmfh.bfType = 19778;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;
    if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
        return 0;
    if (Written < sizeof(BITMAPINFOHEADER))
        return 0;
    int PalEntries;
    if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
                      (int)(1 << lpbi->bmiHeader.biBitCount) : 0;
    if(lpbi->bmiHeader.biClrUsed)
    PalEntries = lpbi->bmiHeader.biClrUsed;
    if(PalEntries){
    if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
        return 0;
        if (Written < PalEntries * sizeof(RGBQUAD))
            return 0;
    }
    bmfh.bfOffBits = GetFilePointer(BmpFile);
    if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
        return 0;
    if (Written < lpbi->bmiHeader.biSizeImage)
        return 0;
    bmfh.bfSize = GetFilePointer(BmpFile);
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;


    CloseHandle (BmpFile);

    delete [] (char*)lpvBits;
    delete [] lpbi;

    Win32::DeleteDC (OffscrDC);
    Win32::DeleteObject (OffscrBmp);

    return 1;

    }

bool ScreenCapture(int x, int y, int width, int height, char *filename, HWND hwnd)
{
    HDC hDC= GetDC(hwnd);
    HDC hDc = Win32::CreateCompatibleDC(hDC);

    HBITMAP hBmp = Win32::CreateCompatibleBitmap(hDC, width, height);

    HGDIOBJ old= Win32::SelectObject(hDc, hBmp);
    Win32::BitBlt(hDc, 0, 0, width, height, hDC, x, y, SRCCOPY);

    bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);

    Win32::SelectObject(hDc, old);
    Win32::DeleteObject(hBmp);

    Win32::DeleteDC (hDc);
    ReleaseDC (hwnd, hDC);

    return ret;
}


