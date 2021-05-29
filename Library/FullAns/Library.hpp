#ifndef Library_HPP
#define Library_HPP
#include <string>
#include <windows.h>
#include <vector>
#include "sqlite3/sqlite3.h"
#include <ctime>

using namespace std;

enum Genre
{
	Action,
	Classic,
	Comic,
	Mystery,
	Fantasy
};

struct Book
{
	unsigned short Year;
	unsigned short Edition;
	Genre gener;
	string Writer;
	string Name;
	string DataTime;
	long int Primary_Key;
};
struct Person
{
	string Fname;
	string Lname;
	string PhoneNo;
	string Mail;
};
struct BorrowBook : public Book
{
	string DeliveryDate;
	string ReturnDate;
	Person person;
};

class LibraryDataBase
{
private:
	vector<Book> Books;
	vector<BorrowBook> BorrowBooks;

#define Error_SaveBook "Can not Save Book !"
#define Error_NotFound "The Book Not Found!"

	void DBException(string err)
	{

		throw "DataBase Error : " + err;
	}
	long int CreatPrimaryKey()
	{
		long int res;
		char* zErrMsg;

		while (true)
		{
			vector<Book>* Allbook = new vector<Book>;
			res = rand() % (100000 - 1000) + 1000;
			string sql = "SELECT * FROM Books WHERE Id == "+ to_string(res) +";";
			int rc = sqlite3_exec(db, sql.c_str(), Selectcallback, (void*)Allbook, &zErrMsg);
			if (Allbook->size() == 0)
				break;
		}
		return res;
	}
	sqlite3* db;
	string SETDATA( Book book)
	{
		
		string data = "INSERT INTO Books (ID,RigesterDataTime,Year,Writer,Name,Gener,Edition) "  \
			"VALUES(" + to_string(book.Primary_Key)+ ", '" + book.DataTime + "', "+to_string(book.Year)+", "\
			"'"+ book.Writer+"', '"+ book.Name +"', '"+ to_string((int)book.gener) +"', "+to_string(book.Edition)+"); ";
		return data;
	}

public:

	LibraryDataBase()
	{

		
		char* zErrMsg = 0;
		int rc;


		/* Open database */
		rc = sqlite3_open("LibraryBook.db", &db);

		if (rc) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		}
		else {
			fprintf(stderr, "Opened database successfully\n");
		}
	}
	~LibraryDataBase() { sqlite3_close(db); }

	static int Selectcallback(void* data, int argc, char** argv, char** azColName) {
		Book selectedbook ;
		selectedbook.Primary_Key = stoi(argv[0]);
		selectedbook.DataTime = argv[1];
		selectedbook.Year = stoi(argv[2]);
		selectedbook.Writer = argv[3];
		selectedbook.Name = argv[4];
		selectedbook.gener = (Genre)stoi(argv[5]);
		selectedbook.Edition = stoi(argv[6]);
		((vector<Book>*)data)->push_back(selectedbook);
		return 0;
	}

	static int callback(void* notused, int argc, char** argv, char** azcolname) {
		string res = "";
		int i;
		for (i = 0; i < argc; i++) {
			string str1 = string(argv[i]);
			string str2 = string(azcolname[i]);
			string str3 = argv[i] ? str1 : "null";
			res += str2 + " = " + str3 + "\n";
		}
		throw res;
		return 0;
	}

	/// <summary>
	/// Save Book in Data base
	/// </summary>
	/// <param name="book"></param>
	/// <returns>Primary key Of Book</returns>
	long int SaveBook(Book book)
	{

		book.Primary_Key = CreatPrimaryKey();
		string sql ;
		char* zErrMsg;
		sql = SETDATA(book);		
		int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

		if (rc != SQLITE_OK) {
			char* err = new char;
			sprintf(err, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			throw err;
			
		}
		//Books.push_back(book);
		return book.Primary_Key;
		DBException(Error_SaveBook);

	}
	void DeleteBook(long int id)
	{
		for (auto tar = Books.begin(); tar < Books.end(); tar++)
		{
			if ((*tar).Primary_Key == id)
			{
				Books.erase(tar);
				return;
			}
		}
		DBException(Error_NotFound);
	}
	vector<Book> GetBooks()
	{
		return Books;
	}
	vector<BorrowBook> GetBorrowBooks()
	{
		return BorrowBooks;
	}
	void AddBorrowBooks(BorrowBook b)
	{
		BorrowBooks.push_back(b);
	}
	void DeleteBorrowBooks(long int id)
	{
		for (auto tar = BorrowBooks.begin(); tar < BorrowBooks.end(); tar++)
		{
			if ((*tar).Primary_Key == id)
			{
				BorrowBooks.erase(tar);
				return;
			}
		}
		DBException(Error_NotFound);
	}
};

class Library
{
private:
	LibraryDataBase DB = LibraryDataBase();
	vector<BorrowBook> BorrowBooks;

public:
	long int SaveBook(string DataTime, string Name, string Writer, unsigned short Year, unsigned short Edition, Genre gener)
	{
		Book newbook
		{
			Year,
			Edition,
			gener,
			Writer,
			Name,
			DataTime
		};
		return DB.SaveBook(newbook);
		throw exception("Book Information Incorrect !");
	}
	void DeleteBook(long int id)
	{
		DB.DeleteBook(id);
	}
	vector<Book> FilterGenre(Genre g)
	{

		vector<Book> AllBook = DB.GetBooks();
		vector<Book> res;
		for (auto tar : AllBook)
			if (tar.gener == g)
				res.push_back(tar);
		if (!res.empty())
			return res;
		else
			throw "No items found !";
	}
	bool Borrowbook(Book book, string DeliveryDate, string ReturnData, Person person)
	{

		vector<BorrowBook> bb = DB.GetBorrowBooks();
		for (auto tar : bb)
			if (tar.Primary_Key == book.Primary_Key)
				throw "Error Book Borrowed ...";

		BorrowBook newBB;
		newBB.DataTime = book.DataTime;
		newBB.DeliveryDate = DeliveryDate;
		newBB.Edition = book.Edition;
		newBB.gener = book.gener;
		newBB.Name = book.Name;
		newBB.person = person;
		newBB.Primary_Key = book.Primary_Key;
		newBB.ReturnDate = ReturnData;
		newBB.Writer = book.Writer;
		DB.AddBorrowBooks(newBB);
	}
	static string  CurrentTime()
	{
		char* data = new char;
		time_t now = time(0);
		tm* datatime = localtime(&now);
		sprintf(data, "%i / %i / %i ", datatime->tm_year, datatime->tm_mon, datatime->tm_mday);
		return string(data);
	}
};



#endif // !Library_HPP

