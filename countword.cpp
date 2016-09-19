#include "config.h"
#include <algorithm>
#include <map>
#include <cwctype>
#include <cwchar>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const int MAXN = 4;
map<ull, int> counts[MAXN + 1];

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
		for(int len = 1; len <= MAXN; ++len) {
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
			for(int i = 1; i <= MAXN; ++i)
				printf("%d ", sz(counts[i]));
			puts("");
			if(cntSentences > 5000000) break;
		}
	}
	in.close();

	int countwords = 0;
	for(int length = MAXN; length >= 1; --length) {
		foreach(w, counts[length]) {
			int a[10], len;
			decrypt(w->first, a, len);
			ull firstword = a[0];
			if(a[0] > 128 && len > 1)
				firstword = (firstword << 8) | a[1];
			double p = w->second * 1. / counts[1][firstword];
			if(p > 0.15 && w->second > 150) {
				for(int i = 0; i < len; ++i)
					out << (wchar_t) a[i];
				out << " " << ++countwords << endl;
				out << flush;

				int b[4], idx = 0;
				for(int i = 0; i < length; ++i) {
					b[i] = 0;
					if(idx < len) {
						b[i] = a[idx++];
						if(b[i] > 128 && idx < len)
							b[i] = (b[i] << 8) | a[idx++];
					}
				}
				for(int _length = length - 1; _length >= 2; --_length) {
					for(int head = 0; head < length; ++head) {
						if(head + _length > length) break;
						ull code = 0;
						for(int i = 0; i < _length; ++i)
							code = (code << 16) | b[i + head];
						counts[_length][code] -= w->second;
					}
				}
			}
		}
	}
	out.close();
	return 0;
}

