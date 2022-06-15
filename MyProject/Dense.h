#ifndef _DENSE_H
#define _DENSE_H
using std::endl;
using std::cout;
#include<vector>

// Gaussian Elimination
template<typename T>
Zuth::Matrix<T> gaussianElimination(Zuth::Matrix<T> m) {
    int row = m.getRowSize();
    int col = m.getColSize();
    Zuth::Matrix<T> ans(m);
    for (int i = 0; i < row - 1; i++) {// 选取主行
        double num = ans.getNum(i, i);
        for (int j = i + 1; j < row; j++) {// 其他行
            double mul = ans.getNum(j, i) / num;
            for (int k = i; k < col; k++)
                ans.getNum(j, k) -= mul * ans.getNum(i, k);
        }
    }
    for (int i = row - 1; i > 0; i--) {// 选取主行
        double num = ans.getNum(i, i);
        for (int j = i - 1; j >= 0; j--) {// 其他行
            double mul = ans.getNum(j, i) / num;
            for (int k = 0; k < col; k++)
                ans.getNum(j, k) -= mul * ans.getNum(i, k);
        }
    }

    return ans;
}
// LU分解求解
template<typename T>
Zuth::Vector<T> LUsolve(Zuth::Matrix<T> m){
    int row = m.getRowSize();
    int col = m.getColSize();
    Zuth::Matrix<T> temp=gaussianElimination(m);
    Zuth::Vector<T> ans(col-1);
    for (int i = 0; i < col-1; i++)ans[i] = temp.getNum(i, col - 1) / temp.getNum(i,i);
    return ans;
}

template<typename T>
Zuth::Vector<Zuth::Matrix<T> > QR(Zuth::Matrix<T> M) {
	int m = M.getRowSize();
	int n = M.getColSize();
	double** A = new double* [m];
	for (int i = 0; i < m; i++) A[i] = new double[m];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = M.getNum(i, j);
		int i, j, k, nn, jj;
		double u, alpha, w, t;
		double** Q = new double* [m];   //动态分配内存空间
		for (i = 0; i < m; i++) Q[i] = new double[m];
		if (m < n)
		{
			cout << "\nQR分解失败！" << endl;
			exit(1);
		}
		//保证列数<=行数
		for (i = 0; i <= m - 1; i++)
			for (j = 0; j <= m - 1; j++)
			{
				Q[i][j] = 0.0;
				if (i == j) Q[i][j] = 1.0;
			}
		//初始的Q矩阵就是一个单位的m阶方阵
		nn = n;
		if (m == n) nn = m - 1;
		for (k = 0; k <= nn - 1; k++)//在大循环k：0~m当中，进行H矩阵的求解，左乘Q，以及左乘A
		{

			u = 0.0;
			for (i = k; i <= m - 1; i++)
			{
				w = fabs(A[i][k]);
				if (w > u) u = w;
			}
			alpha = 0.0;
			for (i = k; i <= m - 1; i++)
			{
				t = A[i][k] / u; alpha = alpha + t * t;
			}
			if (A[k][k] > 0.0) u = -u;
			alpha = u * sqrt(alpha);
			if (fabs(alpha) + 1.0 == 1.0)
			{
				cout << "\nQR分解失败！" << endl;
				exit(1);
			}

			u = sqrt(2.0 * alpha * (alpha - A[k][k]));
			if ((u + 1.0) != 1.0)
			{
				A[k][k] = (A[k][k] - alpha) / u;
				for (i = k + 1; i <= m - 1; i++) A[i][k] = A[i][k] / u;

				//以上就是H矩阵的求得，实际上程序并没有设置任何数据结构来存储H矩
				//阵，而是直接将u向量的元素赋值给原A矩阵的原列向量相应的位置，这样做
				//这样做是为了计算左乘矩阵Q和A
				for (j = 0; j <= m - 1; j++)
				{
					t = 0.0;
					for (jj = k; jj <= m - 1; jj++)
						t = t + A[jj][k] * Q[jj][j];
					for (i = k; i <= m - 1; i++)
						Q[i][j] = Q[i][j] - 2.0 * t * A[i][k];
				}
				//左乘矩阵Q，循环结束后得到一个矩阵，再将这个矩阵转置一下就得到QR分解中的Q矩阵
				//也就是正交矩阵

				for (j = k + 1; j <= n - 1; j++)
				{
					t = 0.0;
					for (jj = k; jj <= m - 1; jj++)
						t = t + A[jj][k] * A[jj][j];
					for (i = k; i <= m - 1; i++)
						A[i][j] = A[i][j] - 2.0 * t * A[i][k];
				}
				//H矩阵左乘A矩阵，循环完成之后，其上三角部分的数据就是上三角矩阵R
				A[k][k] = alpha;
				for (i = k + 1; i <= m - 1; i++)  A[i][k] = 0.0;
			}
		}
		for (i = 0; i <= m - 2; i++)
			for (j = i + 1; j <= m - 1; j++)
			{
				t = Q[i][j]; Q[i][j] = Q[j][i]; Q[j][i] = t;
			}
		Zuth::Matrix<T> Q1(m, n, Q);
		Zuth::Matrix<T> A1(m, n, A);
		Zuth::Vector<Zuth::Matrix<T> > ans;
		ans.pushback(Q1);
		ans.pushback(A1);
		return ans;
}

template<typename T>
Zuth::Vector<T> QRsolve(Zuth::Matrix<T> M) {
	
	int col = M.getColSize();
	int row = M.getRowSize();
	Zuth::Vector<T> ans(row);
	Zuth::Matrix<T> b(M.block(0, col - 1, row - 1, col - 1));
	Zuth::Matrix<T> newM(M.block(0, 0, row - 1, row - 1));
	Zuth::Vector<Zuth::Matrix<T> > QRV = QR(newM);
	Zuth::Matrix<T> Q = QRV[0];
	Zuth::Matrix<T> R = QRV[1];
	//cout << Q << endl << R;
	b = Zuth::Transpose(Q) * b;
	//cout << R << b;
	for (int i = row - 1; i >= 0; i--) {// 求解
		double num = b.getNum(i, 0);
		for (int j = i + 1; j < row; j++)
			num -= ans[j] * R.getNum(i, j);
		ans[i] =num/ R.getNum(i, i);
	}
	return ans;
}
// 最小二乘
template<typename T>
class CurveFit {
	double Em[6][4];
public:
	CurveFit(std::vector<double> Vx, std::vector<double> Vy, int n, int ex, double coefficient[]) {
		EMatrix(Vx, Vy, n, ex, coefficient);
	}
	double sum(std::vector<double> Vnum, int n)
	{
		double dsum = 0;
		for (int i = 0; i < n; i++)
		{
			dsum += Vnum[i];
		}
		return dsum;
	}
	//乘积和
	double MutilSum(std::vector<double> Vx, std::vector<double> Vy, int n)
	{
		double dMultiSum = 0;
		for (int i = 0; i < n; i++)
		{
			dMultiSum += Vx[i] * Vy[i];
		}
		return dMultiSum;
	}
	//ex次方和
	double RelatePow(std::vector<double> Vx, int n, int ex)
	{
		double ReSum = 0;
		for (int i = 0; i < n; i++)
		{
			ReSum += pow(Vx[i], ex);
		}
		return ReSum;
	}
	//x的ex次方与y的乘积的累加
	double RelateMutiXY(std::vector<double> Vx, std::vector<double> Vy, int n, int ex)
	{
		double dReMultiSum = 0;
		for (int i = 0; i < n; i++)
		{
			dReMultiSum += pow(Vx[i], ex) * Vy[i];
		}
		return dReMultiSum;
	}
	//计算方程组的增广矩阵
	void EMatrix(std::vector<double> Vx, std::vector<double> Vy, int n, int ex, double coefficient[])
	{
		for (int i = 1; i <= ex; i++)
		{
			for (int j = 1; j <= ex; j++)
			{
				Em[i][j] = RelatePow(Vx, n, i + j - 2);
			}
			Em[i][ex + 1] = RelateMutiXY(Vx, Vy, n, i - 1);
		}
		Em[1][1] = n;
		CalEquation(ex, coefficient);
	}
	//求解方程
	void CalEquation(int exp, double coefficient[])
	{
		for (int k = 1; k < exp; k++) //消元过程
		{
			for (int i = k + 1; i < exp + 1; i++)
			{
				double p1 = 0;

				if (Em[k][k] != 0)
					p1 = Em[i][k] / Em[k][k];

				for (int j = k; j < exp + 2; j++)
					Em[i][j] = Em[i][j] - Em[k][j] * p1;
			}
		}
		coefficient[exp] = Em[exp][exp + 1] / Em[exp][exp];
		for (int l = exp - 1; l >= 1; l--)   //回代求解
			coefficient[l] = (Em[l][exp + 1] - F(coefficient, l + 1, exp)) / Em[l][l];
	}
	//供CalEquation函数调用
	double F(double c[], int l, int m)
	{
		double sum = 0;
		for (int i = l; i <= m; i++)
			sum += Em[l - 1][i] * c[i];
		return sum;
	}
};

#endif
