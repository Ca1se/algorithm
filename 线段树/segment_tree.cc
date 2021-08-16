#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1000 + 5;

int arr[maxn], l, r, c;
int seg[maxn << 2], lazy[maxn << 2];

void Build(int l, int r, int p) {
	if(l == r) {
		seg[p] = arr[l];
		return;
	}

	int m = l + ((r - l) >> 1);
	Build(l, m, p << 1);
	Build(m + 1, r, (p << 1) | 1);
	seg[p] = seg[p << 1] + seg[(p << 1) | 1];
}

void CheckLazy(int f, int t, int m, int p) {
	if(lazy[p] && f != t) {
		seg[p << 1] += (m - f + 1) * lazy[p];
		seg[(p << 1) | 1] += (t - m) * lazy[p];
		lazy[p << 1] += lazy[p];
		lazy[(p << 1) | 1] += lazy[p];
		lazy[p] = 0;
	}
}

void Update(int f, int t, int p) {
	if(l <= f && t <= r) {
		seg[p] += (t - f + 1) * c;
		lazy[p] = c;
		return;
	}
	int m = f + ((t - f) >> 1);
	CheckLazy(f, t, m, p);
	if(l <= m) Update(f, m, p << 1);
	if(m < r) Update(m + 1, t, (p << 1) | 1);
}

ll Query(int f, int t, int p) {
	if(l <= f && t <= r) {
		return seg[p];
	}
	int m = f + ((t - f) >> 1);
	ll sum = 0;
	CheckLazy(f, t, m, p);
	if(l <= m) sum = Query(f, m, p << 1);
	if(m < r) sum += Query(m + 1, t, (p << 1) | 1);
	return sum;
}

int main() {
	memset(seg, 0, sizeof seg);
	memset(lazy, 0, sizeof lazy);
	int n, m, f, t, choose;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d", arr + i);
	}
	Build(1, n, 1);
	for(int i = 0; i < m; i++) {
		// 1 for Query, 0 for modify
		scanf("%d%d%d", &choose, &l, &r);
		if(choose) {
			printf("%lld\n", Query(1, n, 1));
		}else {
			scanf("%d", &c);
			Update(1, n, 1);
		}
	}
	return 0;
}
