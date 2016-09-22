#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cwchar>
#include <cmath>
#include <algorithm>
#include <cwctype>
#include <cstring>
#include "config.h"
#include <sstream>
#include <fstream>
using namespace std;

int main() {
	wifstream in("data\\relation.txt", wifstream::in);
	wofstream out("data\\test.txt", wofstream::out);
	ios::sync_with_stdio(false);
	setlocale(LC_ALL, "chs");
	wstring lines, str;
	int cntSentences = 0;
	while(getline(in, lines)) {
		wstringstream input(lines, wstringstream::in);
		input >> str;
		int pos = str.find((wchar_t) '-');
		out << str.substr(0, pos) << " ";
		out << str.substr(pos + 1, sz(str) - pos) << " ";
		input >> str;
		out << str << endl;

		if(++cntSentences % 100) out << flush;
	}
	in.close(), out.close();
	return 0;
}


