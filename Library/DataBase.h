#pragma once
#include "BookModel.h"
#include "json.hpp"
#include <fstream>
#include <cstdio> // for rename or delete file
using namespace std;
#ifndef DataBase_H
#define DataBase_H
class DataBase
{
public:
	DataBase(){}
	void Insert(Book book);
	void Delete(long int PK);
	void Update(Book book);
	Book Read(long int PK);
private:
	inline string SetExtention(string Filename , string Ex);
};
#endif // !DataBase_H


