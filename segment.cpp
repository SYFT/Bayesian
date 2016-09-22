void cut(const wstring &data, int pos, vector<int>& words) {
	if(pos >= sz(data)) bayesianScore(words);
	else if(isSymbol(data, pos)) {
		words.push_back(data.substr(pos, 1));
		cut(data, pos + 1, words);
		words.pop_back();
	} else {
		for(int len = 1; pos + len <= sz(data); ++len) {
		}
	}
}

wstring Segment::SlowSegment::segment(const wstring &originData) {
	result = originData, maxScore = 0.;
	vector<int> segs;
	cut(originData, 0, segs);
	return result;
}

void Segment::init() {
	puts("Begin to load glossary and relation.");
	puts("Please wait. It will last up to 1 minute.")
	loadGlossaryAndRelation(index, relation);
	puts("Finished loading.")

	puts("Begin to initialize.");
	puts("Initialization done.")
}

wstring Segment::slowSegment(const wstring &sentence) {
	wstring ret = SlowSegment::segment(sentence);
	return ret;
}

