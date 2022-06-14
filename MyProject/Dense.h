#ifndef _DENSE_H
#define _DENSE_H

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

#endif
