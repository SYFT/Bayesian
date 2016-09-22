#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
#include "config.h"
#include "global.h"
#include <map>
using namespace std;

class SlowSegment {
	private :
		static wstring result;

	public :
		static void bayesianScore(const vector<int> &words) ;

		static void cut(const wstring &data, int pos) ;

		static wstring segment(const wstring &originData) ;
};

wstring slowSegment(const wstring &sentence) ;

#endif

