#ifndef _VECTOR_H
# define  _VECTOR_H

template<typename Type>
class Vector {
	int cap;
	int size;
	Type* pointer;
public:
	// 普通构造
	Vector() {
		cap = 1;
		size = 0;
		pointer = new Type[cap];
	}
	// 给定长度的构造
	Vector(int len) {
		cap = 1;
		size = 0;
		pointer = new Type[cap];
		// 填0
		for (int i = 0; i < len; i++)pushback(0);
	}
	// 拷贝构造
	Vector(const Vector& tempV) {
		cap = tempV.cap;
		size = tempV.size;
		pointer = new Type[cap];
		for (int i = 0; i < size; i++)
			pointer[i] = tempV.pointer[i];
	}
	// 在数组后面加入元素
	void pushback(const Type &data) {
		if (size == cap)resize(cap * 2);
		pointer[size] = data;
		size++;
	}
	// 移除最后一个元素
	void popback() {
		if (size < cap / 2)resize(cap / 2);
		size--;
	}
	// 调整大小
	void resize(int newCap) {
		Type* newPointer = new Type[newCap];
		for (int i = 0; i < size; i++) 
			newPointer[i] = pointer[i];
		// 更新指针
		pointer = newPointer;
		cap = newCap;
	}
	// 重载[]
	Type & operator[](int i) {
		return pointer[i];
	}
	// 得到数组大小
	int getsize() {
		return size;
	}
};

#endif


