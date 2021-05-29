#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <iostream>
#include "Library.hpp"

using namespace std;

int main()
{
	Library Library;
	int i = Library.SaveBook(Library::CurrentTime(),"C++ Learing","Amirreza Tavakoli" , 2020 , 1 ,Genre::Mystery);
	Library.DeleteBook(i);
	system("pause");
}
