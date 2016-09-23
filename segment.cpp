ll Segment::totWords, Segment::unseen;
map<wstring, int> Segment::index;
map<int, wstring> Segment::backMap;
map<int, int> Segment::counts;
map<Related, int> Segment::relation;
map<int, int> Segment::unseenRelation;

wstring Segment::SlowSegment::result;
double Segment::SlowSegment::maxScore;

void Segment::SlowSegment::bayesianScore(const vector<int> &segs) {
	int len = sz(segs);
	// puts("segs:");
	// for(int i = 0; i < len; ++i) printf("%d ", segs[i]);
	// puts("");
	if(!len) return;

	double p = 1.;
	for(int i = 1, lastWord = totWords + 1; i < len; ++i) {
		if(counts.count(lastWord)) {
			Related tmp(lastWord, segs[i]);
			if(relation.count(tmp))
				p *= relation[tmp] / counts[lastWord];
			else
				p *= unseenRelation[lastWord] / 
					(counts[lastWord] * 1. * 
					 counts[lastWord] * UNSEENRELATION);
		} else {
			if(counts.count(segs[i]))
				p *= counts[segs[i]] / (totWords * 1.);
			else
				p *= unseen / 
					(totWords * 1. * totWords * UNSEENWORDRATIO);
		}

		lastWord = segs[i];
	}
	// printf("%.5lf\n", p);

	if(p > maxScore) {
		maxScore = p;
		result.clear();
		for(int i = 0; i < len; ++i) {
			wstring tmp;
			if(segs[i] >= 0) tmp = backMap[segs[i]];
			else tmp = Global::toWstring(abs(segs[i]));
			result += tmp;
			result.push_back((wchar_t) '/');
		}
		wofstream out("data\\debug.txt", wofstream::out|wofstream::app);
		out << "result:" << result << endl;
		out.close();
	}
}

void Segment::SlowSegment::cut(
		const int *w, int pos, int n, vector<int>& words) {
	if(pos >= n) bayesianScore(words);
	else {
		words.push_back(-w[pos]);
		cut(w, pos + 1, n, words);
		words.pop_back();

		for(int len = 2; pos + len <= n; ++len) {
			wstring tmp = Global::toWstring(w + pos, len);

			if(index.count(tmp)) {
				int idx = index[tmp];
				words.push_back(idx);
				cut(w, pos + len, n, words);
				words.pop_back();
			}
		}
	}
}

wstring Segment::SlowSegment::segment(const wstring &originData) {
	wstring ret;
	static int w[Global::MAXSYMBOLS], len;
	Global::toArray(originData, w, len);

	// for(int i = 0; i < len; ++i) printf("%dd ", w[i]);
	// puts("");
	// foreach(w, Global::symbols) printf("%d ", *w);
	// puts("");


	for(int i = 0, tpos = 0; i <= len; ++i)
		if(i == len || Global::isSymbol(w[i])) {
			vector<int> segs;
			result.clear(), maxScore = -1.; 
			cut(w + tpos, 0, i - tpos, segs);
			tpos = i + 1;

			// printf("%d %.5lf %ls\n", tpos, maxScore, result.c_str());

			wstring theSymbol;
			if(i < len) theSymbol = Global::toWstring(w + i, 1);
			ret += result + theSymbol;
			wofstream out("data\\debug.txt", wofstream::out|wofstream::app);
			out << "ret:" << ret << endl;
			out.close();
		}
	return ret;
}

void Segment::init() {
	puts("Begin to load glossary and relation.");
	puts("Please wait. It will last up to 1 minute.");
	Global::loadAll(index, counts, relation);
	puts("Finished loading.");

	puts("Begin to initialize.");

	puts("Initializing words...");
	backMap.clear();
	foreach(w, index) backMap[w->second] = w->first;

	unseen = 0, totWords = 0;
	foreach(w, counts) {
		totWords += w->second;
		if(w->second > 1 && w->second < 9) {
			int newCount = floor(w->second * DECOUNT);
			unseen += w->second - newCount;
			w->second = newCount;
		}
	}
	puts("Words done.");

	puts("Initailizing relations...");
	unseenRelation.clear();
	foreach(r, relation)
		if(r->second > 1 && r->second < 9) {
			int newCount = floor(r->second * DECOUNT);
			unseenRelation[r->first.first] += r->second - newCount;
			r->second = newCount;
		}
	puts("Relations done.");

	puts("Initialization done.");
}

wstring Segment::slowSegment(const wstring &sentence) {
	wstring ret = SlowSegment::segment(sentence);
	wofstream out("data\\debug.txt", wofstream::out|wofstream::app);
	out << "ret_:" << ret << endl;
	out.close();
	return ret;
}

