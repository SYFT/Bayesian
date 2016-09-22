ll Global::totWords;

void Global::loadSymbols() {
	wifstream in(SYMBOL, wifstream::in);
	symbols.clear();

	wstring line;
	static int w[MAXSYMBOLS], n;
	while(getline(in, line)) {
		toArray(line, w, n);
		for(int i = 0; i < n; ++i) symbols.push_back(w[i]);
	}
	sort(all(symbols));

	in.close();
}

bool isSymbol(const int code) {
	vector<int>::iterator it = lower_bound(all(symbols), code);
	if(it != symbols.end() && *it == code) return true;
	return false;
}

void Global::toArray(const wstring &data, int *w, int &n) {
	n = 0;
	for(int i = 0, len = sz(data); i < len; ++i) {
		int x = (int) data[i];
		if(x > 128 && i < len - 1)
			x = (x << 8) | ((int) data[++i]);
		w[n++] = x;
	}
}

void Global::loadGlossary(map<int, int> &ret, map<int, int> &counts) {
	wifstream in(GLOSSARY, wifstream::in);
	ret.clear(), counts.clear();

	wstring line;
	int totWord = 0;
	totWords = 0;
	while(getline(in, line)) {
		wstring word;
		int x;
		wstringstream input(line, wstringstream::in);
		input >> word >> x;
		totWords += x;
		if(ret.count(word) == 0) ret[word] = totWord++;
		counts[ret[word]] += x;
	}

	in.close();
}

void Global::loadRelation(map<Related, int>, int> &ret, 
		const map<int, int> &index) {
	wifstream in(RELATIONSHIP, wifstream::in);
	ret.clear();

	wstring line;
	while(getline(in, line)) {
		wstringstream input(line, wstringstream::in);
		wstring a, b;
		int x;
		input >> a >> b >> x;
		int idxa = index[a], idxb = index[b];
		ret[make_pair(idxa, idxb)] = x;
	}

	in.close();
}

void Global::loadAll(map<int, int> &index, map<int, int> counts, 
		map<Related, int> &relation) {
	loadSymbols();
	loadGlossary(index, counts);
	loadRelation(relation, index);
}

