#include "acauto.h"
#include "config.h"
#include <cwchar>
#include <cwctype>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void buildACAuto(ACAuto &ac, wifstream &in) {
	wstring str;
	while(getline(in, str)) {
		// printf("%d\n", sz(str));
		ac.addWstring(str);
	}
}

void cutText(ACAuto &ac, wifstream &in, wofstream &out) {
	static int mark[32768];
	static bool shouldOut[32768];
	wstring line, str;
	while(getline(in, line)) {
		wistringstream input(line, wistringstream::in);
		while(input >> str) {
			int n = sz(str);
			ac.mark(str, mark);
			for(int i = n - 1, cnt = 0; i >= 0; --i, --cnt) {
				cnt = max(cnt, mark[i] * 2);
				shouldOut[i] = !(cnt > 0);
			}
			for(int i = 0; i < n; ++i)
				if(shouldOut[i]) out << str[i];
			out << " ";
		}
		out << endl;
	}
}

int main() {
	wifstream stopwords("data\\stopword.txt", wifstream::in);
	wifstream in("data\\test.txt", wifstream::in);
	wofstream out("result\\formatcontent.txt", wofstream::out);
	ACAuto ac;
	buildACAuto(ac, stopwords);
	stopwords.close();
	cutText(ac, in, out);
	in.close(), out.close();
	return 0;
}

