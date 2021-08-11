// 维护树上的路径和
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;

struct Edge {
	int from, to, weight;
	Edge(int f, int t, int w): from(f), to(t), weight(w) {}
};

vector<Edge> edges;
vector<int> efrom[maxn];
vector<vector<int>> heavy_link;

int deep[maxn], father[maxn], in_link[maxn], len[maxn];
int sub_size[maxn], heavy_son[maxn], light_len[maxn];

int TreeBuild(int r, int dep) {
	heavy_son[r] = 0;
	deep[r] = dep;
	sub_size[r] = 1;

	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.from + e.to - r;
		if(target == father[r]) continue;
		father[target] = r;
		sub_size[r] += TreeBuild(target, dep + 1);
		if(sub_size[heavy_son[r]] < sub_size[target]) {
			heavy_son[r] = target;
			light_len[r] = e.weight;
		}
	}
	return sub_size[r];
}

void TreeDecomposition(int r, int w, int pos) {
	in_link[r] = pos;
	auto& link = heavy_link[pos];
	if(link.size()) {
		len[r] = len[link.back()] + w;
	}else {
		len[r] = w;
	}
	link.push_back(r);

	if(heavy_son[r]) {
		TreeDecomposition(heavy_son[r], light_len[r], pos);
		for(int i = 0; i < efrom[r].size(); i++) {
			const auto& e = edges[efrom[r][i]];
			int target = e.from + e.to - r;
			if(target == father[r] || target == heavy_son[r]) continue;
			heavy_link.emplace_back();
			TreeDecomposition(target, e.weight, heavy_link.size() - 1);
		}
	}
}

int query(int x, int y) {
	int res = 0;
	while(in_link[x] != in_link[y]) {
		int xtop = heavy_link[in_link[x]][0], ytop = heavy_link[in_link[y]][0];
		if(deep[xtop] > deep[ytop]) swap(x, y), swap(xtop, ytop);
		res += len[y];
		y = father[ytop];
	}
	return res + abs(len[x] - len[y]);
}

int main() {
	int n, m, f, t, w;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n - 1; i++) {
		scanf("%d%d%d", &f, &t, &w);
		int p = edges.size();
		efrom[f].push_back(p);
		efrom[t].push_back(p);
		edges.emplace_back(f, t, w);
	}

	sub_size[0] = 0;
	TreeBuild(1, 1);

	heavy_link.emplace_back();
	TreeDecomposition(1, 0, 0);

	for(int i = 0; i < m; i++) {
		scanf("%d%d", &f, &t);
		printf("%d\n", query(f, t));
	}

	return 0;
}
