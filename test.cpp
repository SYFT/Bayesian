#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cwchar>
#include <cmath>
#include <algorithm>
#include <cwctype>
#include <cstring>
using namespace std;

int main() {
	freopen("data\\stopword.txt", "r", stdin);
	freopen("result\\test.out", "w", stdout);
	setlocale(LC_ALL, "chs");
	// wchar_t ch;
	// wcin >> ch;
	// wcout << (int) ch << endl;
	// wcout << ch << endl;
	// locale loc("Chinese-simplified");
	// wcin.imbue(loc), wcout.imbue(loc);
	wstring chr;
	wcin >> chr;
#define sz(x) ((int) (x).size())
	int maxx = 0;
	while(getline(wcin, chr))
		maxx = max(maxx, sz(chr));
	wcout << maxx << endl;
	// wcout << ch << endl;
	return 0;
}


