#include "config.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include <map>
map<wstring, int> word;

const int MAXWORD = 2000000;
int numbers[MAXWORD];

int main() {
	ios::sync_with_stdio(false);
	int totWord = 0;
	wstring line;

	// wifstream dic("data\\glossary.txt", wifstream::in);
	// wstring line;
	// while(getline(dic, line)) {
	// 	wstring str;
	// 	int x;
	// 	wstringstream in(line, wstringstream::in);
	// 	in >> str >> x;
	// 	if(word.count(str) == 0) word[str] = totWord++;
	// 	numbers[word[str]] = x;
	// }
	// dic.close();

	wifstream rel("data\\relation.txt", wifstream::in);
	puts("Open relation.txt");
	int cntSentences = 0;
	while(getline(rel, line)) {
		wstringstream in(line, wstringstream::in);
		wstring a, b;
		int x;
		in >> a >> b >> x;

		if(word.count(a) == 0) word[a] = totWord++;
		if(word.count(b) == 0) word[b] = totWord++;
		numbers[word[a]] += x;

		if(++cntSentences % 100000 == 0)
			printf("Finished %d.\n", cntSentences);
	}
	puts("Close relation.txt");
	rel.close();

	wofstream out("data\\test.txt", wofstream::out);
	puts("Open test.txt");
	foreach(w, word) {
		out << w->first << " " << numbers[w->second] << endl;
		out << flush;
	}
	out << flush;
	puts("Close test.txt");
	out.close();

	// for(int i = 0; i < totWord; ++i)
	// 	if(numbers[i]) {
	// 		puts("Exits word that has inequal number of word in glossary and relationship.");
	// 		printf("%d\n", numbers[i]);
	// 		break;
	// 	}
	return 0;
}

