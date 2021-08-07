#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
// 求图的割边
/*

int n, m, tot, num = 0, ver[maxn], low[maxn], dfn[maxn], Next[maxn * 2], head[maxn * 2];
bool bridge[2 * maxn];


void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void tarjan(int root, int by_edge) {
	dfn[root] = low[root] = ++num;

	for(int i = head[root]; i; i = Next[i]) {
		if(!dfn[ver[i]]) {
			tarjan(ver[i], i);
			low[root] = min(low[root], low[ver[i]]);
			if(low[ver[i]] > dfn[root]) {
				bridge[i] = bridge[i ^ 1] = true;
			}
		}else if(i != (by_edge ^ 1)) {
			low[root] = min(low[root], dfn[ver[i]]);
		}
	}
}

int main() {
	memset(bridge, 0, sizeof bridge);
	memset(dfn, 0, sizeof dfn);
	memset(head, 0, sizeof head);
	int f, t;
	tot = 1;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &f, &t);
		add(f, t), add(t, f);
	}
	for(int i = 1; i <= n; i++) {
		if(!dfn[i]) {
			tarjan(i, 0);
		}
	}
	for(int i = 2; i < tot; i += 2) {
		if(bridge[i]) {
			printf("%d %d\n", ver[i], ver[i ^ 1]);
		}
	}
	return 0;
}
*/

// 求图的强联通分量
int dfn[maxn], low[maxn], in_stack[maxn], head[maxn], Next[maxn * 2], ver[maxn], num, tot;
stack<int> s;
vector<vector<int>> res;

void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++num;

	s.push(x); in_stack[x] = 1;
	for(int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}else if(in_stack[x]) {
			low[x] = min(low[x], dfn[y]);
		}
	}

	if(low[x] == dfn[x]) {
		auto& it = res.emplace_back();
		while(s.top() == x) {
			it.push_back(s.top());
			in_stack[s.top()] = 0;
			s.pop();
		}
		it.push_back(s.top());
		in_stack[s.top()] = 0;
		s.pop();
	}
}

int main() {
	memset(dfn, 0, sizeof dfn);
	memset(in_stack, 0, sizeof in_stack);
	memset(head, 0, sizeof head);
	int n, m, x, y;

	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	// 从1到n
	for(int i = 1; i <= n; i++) {
		if(!dfn[i]) {
			tarjan(i);
		}
	}

	for(const auto& it: res) {
		printf("%d", it[0]);
		for(int i = 1; i < it.size(); i++) {
			printf(" %d", it[i]);
		}
		printf("\n"):
	}

	return 0;
}
