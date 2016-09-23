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
#include "segment.h"
#include <fstream>
using namespace std;

int main() {
	// ios::sync_with_stdio(false);

	wifstream in("data\\sentences.txt", wifstream::in);
	wofstream out("data\\test.txt", wofstream::out);
	setlocale(LC_ALL, "chs");

	Segment::init();
	wstring line;
	while(getline(in, line)) {
		wstring result = Segment::slowSegment(line);
		out << result << endl;
		out << flush;
	}

	in.close(), out.close();
	return 0;
}


