// 最近公共祖先
// https://oi-wiki.org/graph/lca/
// example: https://acm.hdu.edu.cn/showproblem.php?pid=2586
#include<bits/stdc++.h>
using namespace std;
const int maxn = 4 * 1e4 + 5;
int n, m;
// 倍增算法
/*
struct Edge {
	Edge(int f, int t, int w): f(f), t(t), w(w) {}
	int f, t, w;
};

int fa[maxn][31], deep[maxn], cost[maxn][31];
vector<Edge> edges;
vector<int> efrom[maxn];

void dfs(int root, int father) {
	fa[root][0] = father;
	deep[root] = deep[father] + 1;

	for(int i = 1; i < 31; i++) {
		fa[root][i] = fa[fa[root][i - 1]][i - 1];
		cost[root][i] = cost[fa[root][i - 1]][i - 1] + cost[root][i - 1];
	}

	for(int i = 0; i < efrom[root].size(); i++) {
		const auto& e = edges[efrom[root][i]];
		int target = e.f + e.t - root;
		if(target == father)	continue;
		cost[target][0] = e.w;
		dfs(target, root);
	}
}

int lca(int f, int t) {
	if(deep[f] > deep[t]) swap(f, t);
	int diff = deep[t] - deep[f], res = 0;
	for(int i = 0; diff; i++, diff >>= 1) {
		if(diff & 1) {
			res += cost[t][i];
			t = fa[t][i];
		}
	}

	if(f == t) return res;

	for(int j = 30; j >= 0 && f != t; j--) {
		if(fa[f][j] != fa[t][j]) {
			res += cost[f][j] + cost[t][j];
			f = fa[f][j], t = fa[t][j];
		}
	}

	return res + cost[f][0] + cost[t][0];
}

int main() {
	int t, v1, v2, w;
	scanf("%d", &t);
	while(t--) {
		edges.clear();
		for(int i = 0; i < maxn; i++) {
			efrom[i].clear();
		}
		memset(fa, 0, sizeof fa);
		memset(cost, 0, sizeof cost);
		memset(deep, 0, sizeof deep);
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n - 1; i++) {
			scanf("%d%d%d", &v1, &v2, &w);
			efrom[v1].push_back(edges.size());
			efrom[v2].push_back(edges.size());
			edges.emplace_back(v1, v2, w);
		}
		dfs(1, 0);
		while(m--) {
			scanf("%d%d", &v1, &v2);
			printf("%d\n", lca(v1, v2));
		}
	}
    return 0;
}
*/

// Tarjan算法
#include <algorithm>
#include <iostream>
using namespace std;

class Edge {
 public:
  int toVertex, fromVertex;
  int next;
  int LCA;
  Edge() : toVertex(-1), fromVertex(-1), next(-1), LCA(-1){};
  Edge(int u, int v, int n) : fromVertex(u), toVertex(v), next(n), LCA(-1){};
};

const int MAX = 100;
int head[MAX], queryHead[MAX];
Edge edge[MAX], queryEdge[MAX];
int parent[MAX], visited[MAX];
int vertexCount, edgeCount, queryCount;

void init() {
  for (int i = 0; i <= vertexCount; i++) {
    parent[i] = i;
  }
}

int find(int x) {
  if (parent[x] == x) {
    return x;
  } else {
    return find(parent[x]);
  }
}

void tarjan(int u) {
  parent[u] = u;
  visited[u] = 1;

  for (int i = head[u]; i != -1; i = edge[i].next) {
    Edge& e = edge[i];
    if (!visited[e.toVertex]) {
      tarjan(e.toVertex);
      parent[e.toVertex] = u;
    }
  }

  for (int i = queryHead[u]; i != -1; i = queryEdge[i].next) {
    Edge& e = queryEdge[i];
    if (visited[e.toVertex]) {
      queryEdge[i ^ 1].LCA = e.LCA = find(e.toVertex);
    }
  }
}

int main() {
  memset(head, 0xff, sizeof(head));
  memset(queryHead, 0xff, sizeof(queryHead));

  cin >> vertexCount >> edgeCount >> queryCount;
  int count = 0;
  for (int i = 0; i < edgeCount; i++) {
    int start = 0, end = 0;
    cin >> start >> end;

    edge[count] = Edge(start, end, head[start]);
    head[start] = count;
    count++;

    edge[count] = Edge(end, start, head[end]);
    head[end] = count;
    count++;
  }

  count = 0;
  for (int i = 0; i < queryCount; i++) {
    int start = 0, end = 0;
    cin >> start >> end;

    queryEdge[count] = Edge(start, end, queryHead[start]);
    queryHead[start] = count;
    count++;

    queryEdge[count] = Edge(end, start, queryHead[end]);
    queryHead[end] = count;
    count++;
  }

  init();
  tarjan(1);

  for (int i = 0; i < queryCount; i++) {
    Edge& e = queryEdge[i * 2];
    cout << "(" << e.fromVertex << "," << e.toVertex << ") " << e.LCA << endl;
  }

  return 0;
}
