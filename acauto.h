#ifndef ACAUTO_H
#define ACAUTO_H

#include "config.h"
#include <map>
#include <cwchar>
#include <cwctype>
#include <iostream>
#include <queue>
using namespace std;

class ACAuto {
	static const int N = 4010 * 12;
	private :
		class Node {
			public :
				map<int, int> child;
				int dangerLen, fail;

				Node() {
					child.clear();
					dangerLen = 0, fail = 0;
				}
		} tr[N];

		int rot, tot;

	public :
		ACAuto() {
			rot = 0, tot = 1;
			tr[rot].dangerLen = 0, tr[rot].fail = 0;
		}

		void addWstring(const wstring &str);

		void build();

		void mark(const wstring &str, int *danger);
} ;

#include "acauto.cpp"

#endif
