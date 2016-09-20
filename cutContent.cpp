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
		int n = sz(str);
		if(n == 0) continue;
		// for(int i = 0; i < n; ++i) printf("%d ", (int) str[i]);
		// puts("");
		// printf("%d\n", sz(str));
		// printf("%d\n", (int) str[0]);
		ac.addWstring(str);
		/*debug*/
		// if(!(sz(str) == 2 && (int) str[0] > 150))
		// 	out << str << endl;
	}
	ac.build();
	printf("%d\n", ac.size());
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
				cnt = max(cnt, mark[i]);
				shouldOut[i] = !(cnt > 0);
			}
			bool space = false;
			for(int i = 0; i < n; ++i)
				if(shouldOut[i]) space = true, out << str[i];
				else if(space) space = false, out << " ";
			out << " ";
			// for(int i = 0; i < n; ++i) out << str[i];
			// out << " ";
		}
		out << endl;
		out << flush;
	}
}

int main() {
	ios::sync_with_stdio(false);
	wifstream stopwords("data\\stopword.txt", wifstream::in);
	wifstream in("data\\content.txt", wifstream::in);
	wofstream out("data\\formatcontent.txt", wofstream::out);
	ACAuto ac;
	buildACAuto(ac, stopwords);
	stopwords.close();
	cutText(ac, in, out);
	in.close(), out.close();
	return 0;
}

