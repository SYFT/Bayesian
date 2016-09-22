void loadGlossary(map<wstring, int> &ret) {
	wifstream in(GLOSSARY, wifstream::in);
	ret.clear();

	wstring line;
	int totWord = 0;
	while(getline(in, line)) {
		wstring word;
		wstringstream input(line, wstringstream::in);
		input >> word;
		if(ret.count(word) == 0) ret[word] = totWord++;
	}

	in.close();
}

void loadRelation(map<Related, int>, int> &ret, 
		const map<wstring, int> &index) {
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

void loadGlossaryAndRelation(map<wstring, int> &index,
		map<int, int> &relation) {
	loadGlossary(index);
	loadRelation(relation, index);
}

