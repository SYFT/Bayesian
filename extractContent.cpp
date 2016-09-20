#include <cwchar>
#include <cwctype>
#include "config.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	wifstream in("data\\origindata.txt", wifstream::in);
	wofstream out("data\\content.txt", wofstream::out);
	wstring data;
	wstring ret;
	for(int lineIndex = 1; ; ++lineIndex) {
		if(!getline(in, data)) break;
		if(lineIndex % 6 == 4) {
			ret = data.substr(14, sz(data) - 15 - 14);
			out << ret << endl;
		} else if(lineIndex % 6 == 5) {
			ret = data.substr(9, sz(data) - 10 - 9);
			out << ret << endl;
		}
	}
	return 0;
}

