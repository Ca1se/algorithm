// 快读模板

inline void fast_scanf(int& x) {
	x = 0;
	int s = 1;
	int ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') s = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	x *= s;
}


