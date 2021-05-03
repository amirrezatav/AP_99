#ifndef Library_HPP
#define Library_HPP
#include <string>
#include <windows.h>
#include <vector>
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
		long int res ;
		bool isContain = true;
		while (isContain)
		{
			if (isContain)
			{
				res = rand() % (100000 - 1000) + 1000;
				isContain = false;
			}				
			for (auto tar : Books)
			{
				if(tar.Primary_Key == res)
					isContain = true;
			}
			
		}
		return res;
	}

public:
	/// <summary>
	/// Save Book in Data base
	/// </summary>
	/// <param name="book"></param>
	/// <returns>Primary key Of Book</returns>
	long int SaveBook(Book book)
	{
		book.Primary_Key = CreatPrimaryKey();
			Books.push_back(book);
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
		 LibraryDataBase DB;
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
			if(tar.gener == g)
				res.push_back(tar);
		if (!res.empty())
			return res;
		else
			throw "No items found !";
	}
	 bool Borrowbook (Book book, string DeliveryDate,string ReturnData,Person person)
	{

		vector<BorrowBook> bb = DB.GetBorrowBooks();
		for (auto tar : bb)
			if (tar.Primary_Key == book.Primary_Key)
				throw "Error Book Borrowed ...";

		BorrowBook newBB ;
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

};



#endif // !Library_HPP
