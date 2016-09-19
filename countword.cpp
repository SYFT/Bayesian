#include "config.h"
#include <algorithm>
#include <map>
#include <cwctype>
#include <cwchar>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

map<ull, int> counts[5];

void solve(const wstring &str) {
	static int w[1 << 16], n;
	int m = sz(str);
	n = 0;
	for(int i = 0; i < m; ++i) {
		int x = (int) str[i];
		if(i < m - 1 && x > 128)
			x = (x << 8) | ((int) str[++i]);
		w[n++] = x;
	}

	for(int i = 0; i < n; ++i) {
		ull key = 0;
		for(int len = 1; len <= 4; ++len) {
			if(i + len > n) break;
			key = (key << 16) | w[i + len - 1];
			++counts[len][key];
		}
	}
}

void decrypt(ull s, int w[], int &n) {
	for(n = 0; s; s >>= 16)
		for(int x = s & 65535; x; x >>= 8) w[n++] = x & 255;
	reverse(w, w + n);
}

int main() {
	wifstream in("data\\formatcontent.txt", wifstream::in);
	wofstream out("result\\words.txt", wofstream::out);
	ios::sync_with_stdio(false);
	for(int len = 0; len < 5; ++len) counts[len].clear();
	wstring str;
	int cntSentences = 0;
	while(in >> str) {
		solve(str);
		if(++cntSentences % 100000 == 0) {
			printf("%d\n", cntSentences);
			for(int i = 1; i < 5; ++i)
				printf("%d ", sz(counts[i]));
			puts("");
			if(cntSentences > 10000000) break;
		}
	}

	foreach(w, counts[1]) {
		int a[4], len;
		decrypt(w->first, a, len);
		for(int i = 0; i < len; ++i) out << (wchar_t) a[i];
		out << " " << w->second << endl;
		out << flush;
	}
	in.close(), out.close();
	return 0;
}

