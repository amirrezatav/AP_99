//-----------------------------------------------------
// Design Name : Library Practice
// File Name   : BookMode.h
// Coder       : Amirreza Tavakoli
//-----------------------------------------------------
#include <string>
using std::string;
#ifndef BookModel_H
#define BookModel_H
enum Genre
{
	Action,
	Classic,
	Comic,
	Fantasty,
	Mystery
};
struct Book
{
	string Name;
	Genre Genre;
	unsigned short Year;
	string Writer;
	string Date;
	long int PrimaryKey;
};
struct Person
{
	string Fname;
	string Lname;
	string PhoneNo;
	string Mail;
};
struct BorrowingBook :  Book
{
	string DeliveryDateTime;
	string ReturnDateTime;
	Person Person;
};
#endif // !BookModel_H

