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

#endif

