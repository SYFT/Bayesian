#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cwchar>
#include <cwctype>
#include <cstring>
using namespace std;

int main() {
	freopen("data\\stopword.txt", "r", stdin);
	freopen("test.out", "w", stdout);
	setlocale(LC_ALL, "chs");
	wchar_t ch;
	wcin >> ch;
	wcout << (int) ch << endl;
	wcout << ch << endl;
	// locale loc("Chinese-simplified");
	// wcin.imbue(loc), wcout.imbue(loc);
	wstring chr;
	while(getline(wcin, chr))
		wcout << chr << endl;
	// wcout << ch << endl;
	return 0;
}


