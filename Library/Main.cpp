//-----------------------------------------------------
// Design Name : Library Practice
// File Name   : Main.cpp
// Coder       : Amirreza Tavakoli
//-----------------------------------------------------
#include "DataBase.h"
#include <iostream>
int  main()
{
	DataBase db;
	Book book;
	book.Date = "12-9-2020";
	book.Genre = Genre::Action;
	book.Name = "Test";
	book.PrimaryKey = rand()%1000+10000;
	book.Writer = "WTest";
	book.Year = 2020;
	db.Insert(book);
	return 0;
}
