const int ACAuto::N;
void ACAuto::addWstring(const wstring &str) {
	int n = sz(str), now = rot;
	for(int idx = 0; idx < n; ++idx) {
		int x = (int) str[idx];
		if(tr[now].child.count(x) == 0)
			tr[now].child[x] = tot++;
		now = tr[now].child[x];
	}
	tr[now].dangerLen = max(tr[now].dangerLen, n);
}

void ACAuto::build() {
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
	int n = sz(str);
	for(int i = 0; i < n; ++i) danger[i] = 0;
	int now = rot;
	for(int idx = 0; idx < n; ++idx) {
		int ch = (int) str[idx];
		while(now != rot && tr[now].child.count(ch) == 0)
			now = tr[now].fail;
		if(tr[now].child.count(ch)) now = tr[now].child[ch];
		else now = rot;

		danger[idx] = tr[now].dangerLen;
	}
}

