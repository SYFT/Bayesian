const int ACAuto::N;
void ACAuto::addWstring(const wstring &str) {
	/**
	 * Given a wstring, it will add it into AC automation.
	 * */
	int n = sz(str), now = rot;
	if(n < 1) return;
	for(int idx = 0; idx < n; ++idx) {
		int x = (int) str[idx];
		if(idx < n - 1 && x > 128)
			x = (x << 8) | ((int) str[++idx]);
		if(tr[now].child.count(x) == 0)
			tr[now].child[x] = tot++;
		now = tr[now].child[x];
	}
	tr[now].dangerLen = max(tr[now].dangerLen, n);
}

void ACAuto::build() {
	/**
	 * Build fail pointer and max danger length.
	 * */
	queue<int> que;
	que.push(0);
	while(sz(que)) {
		int u = que.front();
		que.pop();
		foreach(c, tr[u].child) {
			int _v = c->first, v = c->second, nex = tr[u].fail;
			while(nex != rot) {
				if(tr[nex].child.count(_v)) break;
				nex = tr[nex].fail;
			}
			if(nex != rot) tr[v].fail = tr[nex].child[_v];
			else tr[v].fail = rot;
			tr[v].dangerLen = max(tr[v].dangerLen, 
					tr[tr[v].fail].dangerLen);

			que.push(v);
		}
	}
}


void ACAuto::mark(const wstring &str, int *danger) {
	/**
	 * Query a wstring and  a int danger array.
	 * it will returns(change) the danger array.
	 * While danger[i] represent the longest stopword
	 * length whose tail located at index i
	 * */
	int n = sz(str);
	for(int i = 0; i < n; ++i) danger[i] = 0;
	int now = rot;
	for(int idx = 0; idx < n; ++idx) {
		int ch = (int) str[idx];
		if(idx < n - 1 && ch > 128)
			ch = (ch << 8) | ((int) str[++idx]);
		while(now != rot && tr[now].child.count(ch) == 0)
			now = tr[now].fail;
		if(tr[now].child.count(ch)) now = tr[now].child[ch];
		else now = rot;

		danger[idx] = tr[now].dangerLen;
	}
}

