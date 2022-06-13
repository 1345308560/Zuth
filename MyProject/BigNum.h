#ifndef _BIG_NUM_H
# define  _BIG_NUM_H


#include "Vector.h"

class BigNum {
	Zuth::Vector<int> V;
public:
	// 无参数构造
	BigNum() {}
	// 使用整数构造
	BigNum(const int &data) {
		int num = data;
		while (num != 0) {
			V.pushback(num % 10);
			num /= 10;
		}
	}
	// 使用string构造
	BigNum(std::string str) {
		for (int i = str.length() - 1; i >= 0; i--)
			V.pushback(str[i] - '0');
	}
	// 使用Vector构造
	BigNum(Zuth::Vector<int> tempV) {
		for (int i = 0; i < tempV.getsize(); i++)V.pushback(tempV[i]);
	}
	// 拷贝构造
	BigNum(const BigNum& tempBigNum) {
		V = tempBigNum.V;
	}
	// 重载加法
	BigNum operator+(BigNum& otherBN) {
		Zuth::Vector<int> newV;
		// 选择较长的作为主串
		if (V.getsize() > otherBN.V.getsize()) {
			newV = V;
			for (int i = 0; i < otherBN.V.getsize(); i++)
				newV[i] += otherBN.V[i];
		}
		else {
			newV = otherBN.V;
			for (int i = 0; i < V.getsize(); i++)
				newV[i] += V[i];
		}
		// 进位
		for(int i=0;i<newV.getsize()-1;i++)
			if (newV[i] >= 10) {
				newV[i + 1] += newV[i] / 10;
				newV[i] %= 10;
			}
		// 增加长度
		while (newV[newV.getsize() - 1] >= 10) {
			int a = newV[newV.getsize() - 1] % 10;
			int b= newV[newV.getsize() - 1] / 10;
			newV[newV.getsize() - 1] = a;
			newV.pushback(b);
		}
		// 构造新大数
		BigNum nBN(newV);
		return nBN;
	}
	// 重载减法
	BigNum operator-(BigNum& otherBN) {
		Zuth::Vector<int> newV=V;
		// 每位计算
		for (int i = 0; i < otherBN.V.getsize(); i++) {
			newV[i] -= otherBN.V[i];
			if (newV[i] < 0) {
				newV[i] += 10;
				newV[i + 1] -= 1;
			}
		}
		// 调整大小
		while (newV[newV.getsize() - 1] == 0) {
			newV.popback();
		}
		BigNum tempB(newV);
		return tempB;
	}
	// 重载乘法
	BigNum operator*(int otherNum) {
		Zuth::Vector<int> newV = V;
		for (int i = 0; i < newV.getsize(); i++) newV[i] *= otherNum;
		for (int i = 0; i < newV.getsize() - 1; i++) {
			if (newV[i] >= 10) {
				newV[i + 1] += newV[i] / 10;
				newV[i] %= 10;
			}
		}
		while (newV[newV.getsize() - 1] >= 10) {
			int newNum = newV[newV.getsize() - 1] / 10;
			newV[newV.getsize() - 1] %= 10;
			newV.pushback(newNum);
		}
		BigNum tempB(newV);
		return tempB;
	}
	BigNum operator*(BigNum& otherBN) {
		Zuth::Vector<int> newV(V.getsize()+otherBN.V.getsize());
		for (int i = 0; i < V.getsize(); i++)
			for (int j = 0; j < otherBN.V.getsize(); j++)
				newV[i+j] += V[i] * otherBN.V[j];
		for (int i = 0; i < newV.getsize() - 1; i++) {
			if (newV[i] >= 10) {
				newV[i + 1] += newV[i] / 10;
				newV[i] %= 10;
			}
		}
		while (newV[newV.getsize() - 1] == 0) {
			newV.popback();
		}
		BigNum tempB(newV);
		return tempB;
	}
	// 重载<<
	friend std::ostream& operator<<(std::ostream& os, BigNum& b)
	{
		for (int i = b.V.getsize() - 1; i > -1; i--)
			os << b.V[i];
		return os;
	}
};

#endif
