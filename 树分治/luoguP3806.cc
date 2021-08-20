#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;
const int maxm = 105;
const int inf = 2e9;
int n, m;

struct Edge {
	Edge(int f, int t, int w): f(f), t(t), w(w) {}
	int f, t, w;
};

vector<Edge> edges;
vector<int> efrom[maxn];

int rt, sum, cnt;
int q[maxm], siz[maxn], maxx[maxn], dd[maxn], dist[maxn];
bool tf[10000010], vis[maxn], ret[maxn];
queue<int> tag;

inline void scanff(int& x) {
	x = 0;
	int ch = getchar(), sg = 1;
	while(ch < '0' || ch > '9') {
		if(ch == '-') sg = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	x *= sg;
}

inline void Add(int x, int y, int w) {
	int len = edges.size();
	efrom[x].push_back(len);
	efrom[y].push_back(len);
	edges.emplace_back(x, y, w);
}

int CalcSize(int r, int fa) {
	siz[r] = 1;
	maxx[r] = 0;
	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(target == fa || vis[target]) continue;
		siz[r] += CalcSize(target, r);
		maxx[r] = max(maxx[r], siz[target]);
	}
	maxx[r] = max(maxx[r], sum - siz[r]);
	if(maxx[r] < maxx[rt]) rt = r;
	return siz[r];
}

void CalcDist(int r, int fa) {
	dd[++cnt] = dist[r];
	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(target == fa || vis[target]) continue;
		dist[target] = dist[r] + e.w;
		CalcDist(target, r);
	}
}

void dfz(int r, int fa) {
	tf[0] = true;
	tag.push(0);
	vis[r] = true;
	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(target == fa || vis[target]) continue;
		dist[target] = e.w;
		CalcDist(target, r);
		for(int j = 1; j <= cnt; j++) {
			for(int k = 0; k < m; k++) {
				if(q[k] >= dd[j]) ret[k] |= tf[q[k] - dd[j]];
			}
		}
		for(int j = 1; j <= cnt; j++) {
			// 这个判断的作用是数组只开到了1e7，但如果边权和大于1e7就会访问越界
			if(dd[j] < 10000010) {
				tag.push(dd[j]);
				tf[dd[j]] = true;
			}
		}
		cnt = 0;
	}
	while(!tag.empty()) {
		tf[tag.front()] = false;
		tag.pop();
	}
	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(target == fa || vis[target]) continue;
		sum = siz[target];
		rt = 0;
		CalcSize(target, r);
		CalcSize(rt, -1);
		dfz(rt, r);
	}
}

int main() {
	int l, r, w;
	scanff(n), scanff(m);
	for(int i = 0; i < n - 1; i++) {
		scanff(l), scanff(r), scanff(w);
		Add(l, r, w);
	}
	for(int i = 0; i < m; i++) scanff(q[i]);
	cnt = rt = 0;
	maxx[rt] = inf;
	sum = n;
	CalcSize(1, -1);
	CalcSize(rt, -1);
	dfz(rt, -1);
	for(int i = 0; i < m; i++) {
		if(ret[i])	printf("AYE\n");
		else printf("NAY\n");
	}
	return 0;
}
