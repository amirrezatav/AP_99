//-----------------------------------------------------
// Design Name : Library Practice
// File Name   : DataBase.cpp
// Coder       : Amirreza Tavakoli
//-----------------------------------------------------
#include "DataBase.h"
#include <iomanip>

using Json = nlohmann::json;
inline string DataBase::SetExtention(string Filename , string Ex)
{
	return  Filename + Ex;
}
void DataBase::Insert(Book book)
{
	Json BookJs;
	BookJs["PrimaryKey"] = book.PrimaryKey;
	BookJs["Name"] = book.Name;
	BookJs["Genre"] = book.Genre;
	BookJs["Year"] = book.Year;
	BookJs["Writer"] = book.Writer;
	BookJs["Date"] = book.Date;
	
	ofstream wb(SetExtention(std::to_string(book.PrimaryKey), ".json"));
	if (!wb)
		throw "Error!";
	wb << setw(4) << BookJs;
	if(wb.bad())
		throw "Error!";
	wb.close();
}
void DataBase::Delete(long int Pk)
{
	string filename = SetExtention(std::to_string(Pk), ".json");
	int res = remove(filename.c_str());
	if (res != 0)
		throw "Error!";
}
Book DataBase::Read(long int Pk)
{
	Json BookJs;
	ifstream rb(SetExtention(std::to_string(Pk), ".json"));
	if (!rb)
		throw "Error!";
	rb >> BookJs;
	Book newbook;
	newbook.Name = BookJs["Name"].get<string>();
	newbook.Date = BookJs["Date"].get<string>();
	newbook.Genre = (Genre)BookJs["Genre"].get<int>();
	newbook.PrimaryKey = BookJs["PrimaryKey"].get<long>();
	newbook.Writer = BookJs["Writer"].get<string>();
	newbook.Year = BookJs["Year"].get<unsigned short>();
	rb.close();
}
void DataBase::Update(Book book)
{
	// 
}
