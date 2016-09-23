vector<int> Global::symbols;
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

bool Global::isSymbol(const int code) {
	vector<int>::iterator it = lower_bound(all(symbols), code);
	if(it != symbols.end() && *it == code) return true;
	return false;
}

void Global::toArray(const wstring &data, int *w, int &n) {
	n = 0;
	for(int i = 0, len = sz(data); i < len; ++i) {
		int x = (int) data[i];
		// if(x > 128 && x < 256 && i < len - 1)
		// 	x = (x << 8) | ((int) data[++i]);
		w[n++] = x;
	}
}

wstring Global::toWstring(const int *w, int len) {
	wstring ret;
	for(int i = 0; i < len; ++i) {
		wstring now;
		now.push_back((wchar_t) w[i]);
		// for(int x = w[i]; x; x >>= 8)
		//  	now.push_back((wchar_t) (x & 255));
		reverse(all(now));
		ret += now;
	}
	return ret;
}

wstring Global::toWstring(const int state) {
	wstring ret;
	ret.push_back((wchar_t) state);
	// for(int x = state; x; x >>= 8)
	// 	ret.push_back((wchar_t) (x & 255));
	reverse(all(ret));
	return ret;
}

void Global::loadGlossary(map<wstring, int> &ret, 
		map<int, int> &counts) {
	wifstream inpu("data\\glossary.txt", wifstream::in);
	ret.clear(), counts.clear();

	wstring line;
	int totWord = 0;
	totWords = 0;

	static int pp[1234], n;

	while(getline(inpu, line)) {
		output << line << endl;

		wstring word;
		int x;
		wstringstream input(line, wstringstream::in);
		input >> word >> x;
		totWords += x;
		if(ret.count(word) == 0) ret[word] = totWord++;
		counts[ret[word]] += x;
	}

	inpu.close();
}

void Global::loadRelation(map<Related, int> &ret, 
		map<wstring, int> &index) {
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

void Global::loadAll(map<wstring, int> &index, map<int, int> &counts, 
		map<Related, int> &relation) {
	loadSymbols();
	loadGlossary(index, counts);
	loadRelation(relation, index);
}

