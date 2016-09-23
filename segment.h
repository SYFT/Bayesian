#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
#include "config.h"
#include <map>
using namespace std;

class Segment {
	private :
		static const double UNSEENWORD = 0.1,
					 DECOUNT = 0.9,
					 UNSEENRELATION = 0.05;

		static map<wstring, int> index;
		static map<int, wstring> backMap;
		static map<int, int> counts;
		static map<Related, int> relation;
		static map<int, int> unseenRelation;
		static ll totWords, unseen;

	public :

		class SlowSegment {
			private :
				static wstring result;
				static double maxScore;

			public :
				static void bayesianScore(const vector<int>&);

				static void cut(const int*, int, int, vector<int>&);

				static wstring segment(const wstring &) ;
		};

		static void init() ;

		static wstring slowSegment(const wstring &sentence) ;
} ;

#include "segment.cpp"

#endif

