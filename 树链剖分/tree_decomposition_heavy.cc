// https://oi-wiki.org/graph/hld/
#include <bits/stdc++.h>
using namespace std;
// number of vertex
const int maxn = 1000 + 5;

struct Edge {
	Edge(int f, int t): from(f), to(t) {}
	int from, to;
};
vector<Edge> edges;
vector<int> efrom[maxn];
vector<vector<int>> heavy_link;
// 结点的父结点， 结点在树上的深度
int father[maxn], deep[maxn];
// 结点的子树大小， 结点的重子结点
int sub_size[maxn], heavy_son[maxn];
// 结点所在重链的pos
int in_link[maxn];

// 第一个 DFS 记录每个结点的父节点（father）、深度（deep）、子树大小（size）、重子节点（hson）
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
		}
	}
	return sub_size[r];
}

// 第二个 DFS 记录所在链的链顶（top，应初始化为结点本身）、重边优先遍历时的 DFS 序（dfn）、DFS 序对应的节点编号（rank）。
void TreeDecomposition(int r, int pos) {
	in_link[r] = pos;
	heavy_link[pos].push_back(r);

	/*
	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.from + e.to - r;
		if(target == father[r]) continue;
		if(target == heavy_son[r]) {
			TreeDecomposition(target, pos);
		}else {
			heavy_link.emplace_back();
			TreeDecomposition(target, heavy_link.size() - 1);
		}
	}
	*/
	if(heavy_son[r]) {
		TreeDecomposition(heavy_son[r], pos);
		for(int i = 0; i < efrom[r].size(); i++) {
			const auto& e = edges[efrom[r][i]];
			int target = e.from + e.to - r;
			if(target == father[r] || target == heavy_son[r]) continue;
			heavy_link.emplace_back();
			TreeDecomposition(target, heavy_link.size() - 1);
		}
	}
}

int main() {
	int n, v, f, t;
	scanf("%d", &n);
	for(int i = 0; i < n - 1; i++) {
		scanf("%d%d", &f, &t);
		efrom[f].push_back(edges.size());
		efrom[t].push_back(edges.size());
		edges.emplace_back(f, t);
	}
	sub_size[0] = 0;
	TreeBuild(1, 1);
	heavy_link.emplace_back();
	TreeDecomposition(1, 0);
	printf("len:%d\n", heavy_link.size());
	for(const auto& link: heavy_link) {
		for(int v: link) {
			printf("%d ", v);
		}
		printf("\n");
	}
	return 0;
}
