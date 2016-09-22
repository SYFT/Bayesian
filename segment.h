#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
#include "config.h"
#include <map>
using namespace std;

class Segment {
	private :
		map<wstring, int> index;
		map<Related, int> relation;
		ll totWords;

	public :

		class SlowSegment {
			private :
				static wstring result;
				static double maxScore;

			public :
				static void bayesianScore(const vector<wstring> &) ;

				static void cut(const wstring &, int, vector<int> &) ;

				static wstring segment(const wstring &) ;
		};

		void init() ;

		wstring slowSegment(const wstring &sentence) ;
} ;

#endif

