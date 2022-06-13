#ifndef _VECTOR_H
# define  _VECTOR_H

template<typename Type>
class Vector {
	int cap;
	int size;
	Type* pointer;
public:
	// ��ͨ����
	Vector() {
		cap = 1;
		size = 0;
		pointer = new Type[cap];
	}
	// �������ȵĹ���
	Vector(int len) {
		cap = 1;
		size = 0;
		pointer = new Type[cap];
		// ��0
		for (int i = 0; i < len; i++)pushback(0);
	}
	// ��������
	Vector(const Vector& tempV) {
		cap = tempV.cap;
		size = tempV.size;
		pointer = new Type[cap];
		for (int i = 0; i < size; i++)
			pointer[i] = tempV.pointer[i];
	}
	// ������������Ԫ��
	void pushback(const Type &data) {
		if (size == cap)resize(cap * 2);
		pointer[size] = data;
		size++;
	}
	// �Ƴ����һ��Ԫ��
	void popback() {
		if (size < cap / 2)resize(cap / 2);
		size--;
	}
	// ������С
	void resize(int newCap) {
		Type* newPointer = new Type[newCap];
		for (int i = 0; i < size; i++) 
			newPointer[i] = pointer[i];
		// ����ָ��
		pointer = newPointer;
		cap = newCap;
	}
	// ����[]
	Type & operator[](int i) {
		return pointer[i];
	}
	// �õ������С
	int getsize() {
		return size;
	}
};

#endif


