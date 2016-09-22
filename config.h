#ifndef CONFIG_H
#define CONFIG_H

#include <cwchar>
#include <cwctype>
#include <iostream>
#define sz(x) ((int) (x).size())
#define foreach(x, y) \
	for(__typeof((y).begin()) x = (y).begin(); x != (y).end(); ++x)
#define all(x) (x).begin(), (x).end()
typedef long long ll;
typedef unsigned long long ull;

#include <string>
#include <cstring>

const char GLOSSARY[] = "data\\glossary.txt";
const char RELATIONSHIP[] = "data\\relation.txt";
const char SYMBOL[] = "data\\symbols.txt";

#include <map>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> Related;

class Global {
	private :
		static vector<int> symbols;
		static const int MAXSYMBOLS = 510;
		static ll totWords;

	public :
		static void loadSymbols();

		static bool isSymbol(const int);

		static void toArray(const wstring&, int*, int&);

		static void loadGlossary(map<int, int>&);

		static void loadRelation(map<Related, int>&, 
				const map<int, int>&);

		static void loadAll(map<int, int>&, 
				map<int, int>&, map<Related, int>&);
} ;

#include "config.cpp"

#endif

