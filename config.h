#ifndef CONFIG_H
#define CONFIG_H

#include <cwchar>
#include <cwctype>
#include <iostream>
#define sz(x) ((int) (x).size())
#define foreach(x, y) \
	for(__typeof((y).begin()) x = (y).begin(); x != (y).end(); ++x)
typedef long long ll;
typedef unsigned long long ull;

#include <string>
#include <cstring>

const char GLOSSARY[] = "data\\glossary.txt";
const char RELATIONSHIP[] = "data\\relation.txt";

#include <map>

using namespace std;

typedef pair<int, int> Related;

void loadGlossary(map<wstring, int> &) ;

void loadRelation(map<int, int> &, const map<wstring, int> &) ;

void loadGlossaryAndRelation(map<wstring, int> &, map<int, int> &);

#endif

