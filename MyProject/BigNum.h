#ifndef _BIG_NUM_H
# define  _BIG_NUM_H


#include "Vector.h"

class BigNum {
	Zuth::Vector<int> V;
public:
	// �޲�������
	BigNum() {}
	// ʹ����������
	BigNum(const int &data) {
		int num = data;
		while (num != 0) {
			V.pushback(num % 10);
			num /= 10;
		}
	}
	// ʹ��string����
	BigNum(std::string str) {
		for (int i = str.length() - 1; i >= 0; i--)
			V.pushback(str[i] - '0');
	}
	// ʹ��Vector����
	BigNum(Zuth::Vector<int> tempV) {
		for (int i = 0; i < tempV.getsize(); i++)V.pushback(tempV[i]);
	}
	// ��������
	BigNum(const BigNum& tempBigNum) {
		V = tempBigNum.V;
	}
	// ���ؼӷ�
	BigNum operator+(BigNum& otherBN) {
		Zuth::Vector<int> newV;
		// ѡ��ϳ�����Ϊ����
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
		// ��λ
		for(int i=0;i<newV.getsize()-1;i++)
			if (newV[i] >= 10) {
				newV[i + 1] += newV[i] / 10;
				newV[i] %= 10;
			}
		// ���ӳ���
		while (newV[newV.getsize() - 1] >= 10) {
			int a = newV[newV.getsize() - 1] % 10;
			int b= newV[newV.getsize() - 1] / 10;
			newV[newV.getsize() - 1] = a;
			newV.pushback(b);
		}
		// �����´���
		BigNum nBN(newV);
		return nBN;
	}
	// ���ؼ���
	BigNum operator-(BigNum& otherBN) {
		Zuth::Vector<int> newV=V;
		// ÿλ����
		for (int i = 0; i < otherBN.V.getsize(); i++) {
			newV[i] -= otherBN.V[i];
			if (newV[i] < 0) {
				newV[i] += 10;
				newV[i + 1] -= 1;
			}
		}
		// ������С
		while (newV[newV.getsize() - 1] == 0) {
			newV.popback();
		}
		BigNum tempB(newV);
		return tempB;
	}
	// ���س˷�
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
	// ����<<
	friend std::ostream& operator<<(std::ostream& os, BigNum& b)
	{
		for (int i = b.V.getsize() - 1; i > -1; i--)
			os << b.V[i];
		return os;
	}
};

#endif
