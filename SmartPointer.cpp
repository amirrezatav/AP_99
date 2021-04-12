#include <iostream>
using namespace std;

template<class T>
class SmartPointer
{
	T* ptr;
public:
	SmartPointer(T* ptr = NULL)//0x00000000
	{
		this->ptr = ptr;
	}
	~SmartPointer()
	{
		delete(ptr);
	}
	T& operator*()
	{
		// a
		return *ptr;//
	}
	T** operator&()
	{
		// 
		T** ptrr = &ptr;
		return &ptr;
	}
	T* Get()
	{
		// &a
		return ptr;
	}
};

int main()
{
	SmartPointer<int> ptr(new int);
	*ptr = 5;
	cout << *ptr << endl;
	cout << &ptr << endl;
	cout << ptr.Get() << endl;
	return 0;
}
