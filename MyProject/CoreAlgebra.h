#ifndef _CORE_ALGEBRA_H
#define  _CORE_ALGEBRA_H

#include "CoreClass.h"


// 矩阵的行列式
template<typename Type>
double Del(Matrix<Type> m) {
	if (m.getRowSize() == 1)return m.getNum(0, 0);
	else if (m.getRowSize() == 2) 
		return m.getNum(0, 0) * m.getNum(1, 1) - m.getNum(1, 0) * m.getNum(0, 1);
	else {
		double ans = 0;
		int col = m.getColSize();
		for (int i = 0; i < col; i++) {
			// 代数余子式
			Type *tempM = new Type[(col - 1) * (col - 1)];
			for (int j = 1; j < col; j++) {// 行
				int tt = 0;
				for (int k = 0; k < col; k++) { // 列
					// 跳过列
					if (i == k)continue;
					tempM[(j - 1) * (col-1) + tt] = m.getNum(j, k);
					tt++;
				}
			}
			Matrix<Type> tM(col-1,col-1,tempM);
			if(i%2==1)
				ans -= m.getNum(0, i) * Del(tM);
			else 
				ans += m.getNum(0, i) * Del(tM);
		}
		return ans;
	}
}

// Eratosthenes Sieve
Zuth::Vector<bool> eratosthenesSieve(int len) {
	Zuth::Vector<bool> isnp;
	int n = len;
	for (int i = 0; i <= n; i++)isnp.pushback(false);
	for (int i = 2; i * i <= n; i++)
		if (!isnp[i])
			for (int j = i * i; j <= n; j += i)
				isnp[j] = 1;
	return isnp;
}
// Euler Sieve
Zuth::Vector<int> eulerSieve(int len) {
	int MAXN = len;
	bool vis[10005]={false};
	int pri[1005]={0};
	int cnt = 0;
	for (int i = 2; i <= MAXN; ++i) {
		if (!vis[i]) {
			pri[cnt++] = i;
		}
		for (int j = 0; j < cnt; ++j) {
			if (1ll * i * pri[j] > MAXN) break;
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				break;
			}
		}
	}
	Zuth::Vector<int> ans;
	for (int i = 0;i<cnt; i++)ans.pushback(pri[i]);
	return ans;
}
// 快速幂
template<typename T>
T quickPower(T a, T b) {
	T res = 1;
	while (b > 0) {
		if (b & 1) res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}
#endif

