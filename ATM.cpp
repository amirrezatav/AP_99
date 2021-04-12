#include <iostream>
#include <string>
#include<vector> //If you do not know what a vector is, use the array
using namespace std;
enum Gender
{
	Male, // 0
	Fimale // 1 
};
// Hashing PassWord
string Hashing(string password)
{
	hash <string> hashing; // variable (objc)
	string hashed = to_string(hashing(password));
	return to_string(hashing(password));
}
struct User
{
private:
#pragma region Variables
	unsigned long int ID; // private set and Public Get
	string Password; // Public set 
	string Fname;// private set and Public Get
	string Laname;// private set and Public Get
	unsigned long int Amount;// Public set and Public Get
	Gender gender;
	bool IsBock = false;
	unsigned short int BockCounter;
#pragma endregion
#pragma region Funcs
	bool IsLet(string input)
	{
		for (auto achar : input)
		{
			if (!((achar >= 'A' && achar <= 'Z') || (achar >= 'a' && achar <= 'z')))
			{
				return false;
			}
		}
		return true;
	}
#pragma endregion
#pragma region Prop
	void SetID(unsigned long int id)
	{
		if (id > 9999)
		{
			this->ID = id;
		}
		else
		{
			throw exception("Number Must be at least 5 Characters !");
		}
	}
	void SetFName(string fname)
	{
		if (IsLet(fname))
		{
			this->Fname = fname;
		}
		else
		{
			throw exception("Enter Correct FName");
		}
	}
	void SetLName(string lname)
	{
		if (IsLet(lname))
		{
			this->Laname = lname;
		}
		else
		{
			throw exception("Enter Correct LName");
		}
	}
	void Setgender(Gender gender)
	{
		this->gender = gender;
	}
#pragma endregion
public:
	unsigned long int GetID()
	{
		return this->ID;
	}
	string GetFname()
	{
		return this->Fname;
	}
	string GetLaname()
	{
		return this->Laname;
	}
	unsigned long int GetAmount()
	{
		return this->Amount;
	}
	void SetAmount(unsigned long int Amount)
	{
		this->Amount = Amount;
	}
	Gender Getgender()
	{
		return this->gender;
	}
	bool IsCorrectPassword(string enterpassword)
	{
		if (!IsBock)
		{
			if (this->Password == Hashing(enterpassword))
			{
				return true;
			}
			else
			{
				BockCounter++;
				if (BockCounter >= 3)
				{
					IsBock = true;
				}
				return false;
			}
		}
		else
		{
			throw exception("Your Account Blocked!");
		}
	}
	friend string Hashing(string password);
	void SetPassword(string password)
	{
		// use Regex for Check Pasword if you want 
		// [a-zA-z1-9]!@#$%^&*()]
		this->Password = password;
	}
	User(unsigned long int ID , string hashedPassword  , string Fname ,
		string Lname , Gender gender, unsigned long int Amount = 0)
	{
		SetID(ID);
		SetFName(Fname);
		SetLName(Lname);
		SetPassword(hashedPassword);
		Setgender(gender);
		this->Amount = Amount;
		this->BockCounter = 0;
	}
};
class ATMMachine
{
private:
	vector<User> users;
	// For Buy Charge 
	unique_ptr<User> Currentuser;
	bool IsLogin;
	friend string Hashing(string password);
public:
	unsigned long int  Register( string Password, string Fname,
		string Lname, Gender gender, unsigned long int Amount = 0)
	{
		unsigned long int ID = rand() % 10000 + 989999;

		for (auto target : users)
		{
			if (target.GetID() != ID)
			{
				break;
			}
			ID = rand() % 10000 + 989999;
		}
		User newuser(ID ,Hashing(Password) , Fname , Lname , gender , Amount);
		users.push_back(newuser);
		return ID;
	}
	bool Login(unsigned long int ID, string Password)
	{
		for (int i = 0 ; i < users.size();i++)
		{
			if (users[i].GetID() == ID)
			{
				if (users[i].IsCorrectPassword(Password))
				{
					Currentuser = make_unique<User>(users[i]);
					IsLogin = true;
					return true;
				}
				else
				{
					throw exception("Your Password is not Correct. ");
				}
			}
			else
			{
				throw exception("User Not Found . ");
			}
		}
	}
	void Logout()
	{
		Currentuser.reset();
		IsLogin = false;
	}
};
int main()
{
	ATMMachine ATMMachine;
	unsigned long int ID = ATMMachine.Register("Admin", "Amirreza", "Tavakoli", Gender::Male);
	cout << "Your ID : " << ID << endl;
	ATMMachine.Login(ID, "Admin");
	cout << "Login";
	//while (true)
	//{
	//	try
	//	{
	//		// DRIVER PROGRAM
	//	}
	//	catch (exception ex) // exception(Error) Handling 
	//	{
	//		cout << ex.what() << endl;
	//	}
	//}
	return 0;
}
