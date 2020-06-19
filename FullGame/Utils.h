#pragma once

#include <Windows.h>

#include <signal.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <vector>


using namespace std;

void DebugOut(wchar_t *fmt, ...);

vector<string> split(string line, string delimeter = "\t");
wstring ToWSTR(string st);

LPCWSTR ToLPCWSTR(string st);


int GetDistanceX(RECT r1, RECT r2);
int GetDistanceY(RECT r1, RECT r2);
int GetRectW(RECT r);
int GetRectH(RECT r);

class Utils
{
public:
	static bool IsOverlapX(RECT r1, RECT r2)
	{
		return !(r1.right < r2.left || r1.left > r2.right);
	}

	static bool IsOverlapY(RECT r1, RECT r2)
	{
		return !(r1.top > r2.bottom || r1.bottom < r2.top);
	}

};

