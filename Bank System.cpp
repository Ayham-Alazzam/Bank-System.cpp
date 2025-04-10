#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkDelete = false;
};

struct sUsers
{
	string UserName;
	string Password;
	int  Permission;
	bool MarkDelete = false;
};

struct sCurrentUser
{
	string UserName;
	string Password;
	int  Permission;
};


enum enMenueChoices { enShowClientList = 1, enAddNewClient = 2, enDleteClient = 3, enUpdateClientInfo = 4, enFindClient = 5, enTransactions = 6, enManageUsers = 7, enLogout = 8 };

enum enTransactionsChoices { enDeposite = 1, enWithDraw = 2, enTotalBalances = 3, enMainMenue = 4 };

enum enUserPermission { pAll = -1, pShowList = 1, pAddClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLogout = 128 };

enum ManageUsersMenue { enListUser = 1, enAddNewUser = 2, enDeleteUser = 3, enUpdateUser = 4, enFindUser = 5, enuMainMenue = 6 };


string ReadString(string message)
{
	string S;
	cout << message << endl;
	cin >> S;
	return S;
}

string ConvertRecordToLine(sClient Client, string seperator = "#//#")
{
	string stString = "";

	stString += Client.AccountNumber + seperator;
	stString += Client.PinCode + seperator;
	stString += Client.Name + seperator;
	stString += Client.Phone + seperator;
	stString += to_string(Client.AccountBalance);

	return stString;
}

vector <string> Split(string S, string delim)
{
	vector <string> vString;
	string word;
	short pos = 0;

	S.erase(0, S.find_first_not_of(" \t"));
	S.erase(S.find_last_not_of(" \t") + 1);

	while ((pos = S.find(delim)) != std::string::npos)
	{
		word = S.substr(0, pos);
		if (word != "")
		{
			vString.push_back(word);
		}
		S.erase(0, pos + delim.length());
	}
	if (S != "")
	{
		vString.push_back(S);
	}

	return vString;
}

sClient ConvertLineToRecord(string line, string seperator = "#//#")
{
	vector <string> vString;
	sClient Client;

	vString = Split(line, seperator);

	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);

	return Client;
}

void PrintClientRecord(sClient Client)
{
	cout << "The following are the client's details\n\n";

	cout << "\nClient's Account Number: ";
	cout << Client.AccountNumber;
	cout << "\nClient's PinCode: ";
	cout << Client.PinCode;
	cout << "\nClient's Name: ";
	cout << Client.Name;
	cout << "\nClient's Phone: ";
	cout << Client.Phone;
	cout << "\nClient's Account Balance: ";
	cout << Client.AccountBalance;
}

void SaveRecordToFile(sClient Client)
{
	fstream ClientFile;
	string stData;

	ClientFile.open("Client.txt", ios::out | ios::app);
	if (ClientFile.is_open())
	{
		stData = ConvertRecordToLine(Client);
		ClientFile << stData << endl;
	}
	ClientFile.close();
}

bool SearchByAccountNumber(string AccountNumber, vector <sClient> Clients, sClient& Client)
{
	for (sClient C : Clients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

vector <sClient> ConvertDataFromFileToRecord()
{
	vector <sClient> Clients;

	string line = "";
	fstream ClientFile;

	ClientFile.open("Client.txt", ios::in);

	while (getline(ClientFile, line))
	{
		sClient Client;

		Client = ConvertLineToRecord(line);
		Clients.push_back(Client);
	}
	ClientFile.close();

	return Clients;
}

sClient ReadNewClient()
{
	sClient Client;
	vector <sClient> Clients = ConvertDataFromFileToRecord();

	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	while (SearchByAccountNumber(Client.AccountNumber, Clients, Client))
	{
		cout << "Client With Account Number [" << Client.AccountNumber << "] is already exist,Enter another.\n";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode? ";

	getline(cin, Client.PinCode);

	cout << "Enter Name? ";

	getline(cin, Client.Name);

	cout << "Enter Phone? ";

	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";

	cin >> Client.AccountBalance;
	cin.ignore();

	SaveRecordToFile(Client);
	//Clients = ConvertDataFromFileToRecord();


	return Client;
}

void AddNewClient()
{
	char Add = 'Y';
	sClient Client;

	while (Add == 'Y' || Add == 'y')
	{
		Client = ReadNewClient();
		SaveRecordToFile(Client);
		cout << "\n\nClient Added Successfully, do you want to addmore clients ? Y / N ? ";
		cin >> Add;
	}
}

void PrintClientRecordForTable(sClient Client)
{
	cout << "| " << left << setw(20) << Client.AccountNumber;
	cout << "| " << left << setw(15) << Client.PinCode;
	cout << "| " << left << setw(30) << Client.Name;
	cout << "| " << left << setw(15) << Client.Phone;
	cout << "| " << left << setw(15) << Client.AccountBalance;
}

void PrintClientsList(vector <sClient> Clients)
{
	cout << "\n\n\t\t\t\t\tClient List (" << Clients.size() << ") Cliient(s)\n";
	cout << "\n____________________________________________________________________________________";
	cout << "______________________\n\n";
	cout << "| " << left << setw(20) << "Account Number ";
	cout << "| " << left << setw(15) << "Pin Code ";
	cout << "| " << left << setw(30) << "Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(15) << "Account Balance";
	cout << "\n____________________________________________________________________________________";
	cout << "______________________\n\n";

	for (sClient C : Clients)
	{
		PrintClientRecordForTable(C);
		cout << endl;
	}
}

void PrintTransactionsList(vector <sClient> Clients)
{
	cout << "\n\n\t\t\t\t\tClient List (" << Clients.size() << ") Cliient(s)\n";
	cout << "\n____________________________________________________________________________________";
	cout << "______________________\n\n";
	cout << "| " << left << setw(20) << "Account Number ";
	cout << "| " << left << setw(30) << "Name";
	cout << "| " << left << setw(15) << "Account Balance";
	cout << "\n____________________________________________________________________________________";
	cout << "______________________\n\n";

	for (sClient C : Clients)
	{
		cout << "| " << left << setw(20) << C.AccountNumber;
		cout << "| " << left << setw(30) << C.Name;
		cout << "| " << left << setw(15) << C.AccountBalance;
		cout << endl;
	}
}

void AddNewClientScreen()
{
	cout << "-----------------------------------\n";
	cout << "\tAdd New Client Screen\n";
	cout << "-----------------------------------\n";
	cout << "\nAdding New Client:\n";
}

void MarkToDelete(string AccountNumber, vector <sClient>& Clients, sClient& Client)
{
	for (sClient& C : Clients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			C.MarkDelete = true;
		}
	}
}

void SaveClientsAfterDeletedToFile(vector <sClient> Clients, sClient& Client)
{
	fstream ClientFile;
	string ClientInfo;
	ClientFile.open("Client.txt", ios::out);

	if (ClientFile.is_open())
	{
		for (sClient C : Clients)
		{
			if (C.MarkDelete == false)
			{
				ClientInfo = ConvertRecordToLine(C);
				ClientFile << ClientInfo << endl;
			}
		}
		ClientFile.close();
	}
}

void DeleteClientFromRecord(string AccountNumber, vector <sClient>& Clients)
{
	sClient Client;
	char sure = 'n';

	if (SearchByAccountNumber(AccountNumber, Clients, Client))
	{
		PrintClientRecord(Client);

		cout << "\n\nAre you sure you want to delete this client? Y/N ";
		cin >> sure;

		if (sure == 'Y' || sure == 'y')
		{
			MarkToDelete(AccountNumber, Clients, Client);
			SaveClientsAfterDeletedToFile(Clients, Client);

			Clients = ConvertDataFromFileToRecord();

			cout << "Client's Deleted Successfuly.\n";
		}

	}
	else
		cout << "Client with Account Number: (" << AccountNumber << ") Not found.\n";
}

void UpdateClientRecord(string AccountNumber, vector <sClient>& Clients)
{
	sClient Client;
	char sure = 'n';

	if (SearchByAccountNumber(AccountNumber, Clients, Client))
	{
		PrintClientRecord(Client);

		cout << "\n\nAre you sure you want to Update this client? Y/N ";
		cin >> sure;

		if (sure == 'Y' || sure == 'y')
		{
			MarkToDelete(AccountNumber, Clients, Client);
			SaveClientsAfterDeletedToFile(Clients, Client);

			Clients = ConvertDataFromFileToRecord();

			Client = ReadNewClient();

			SaveRecordToFile(Client);

			cout << "\nClient's Updated Successfuly.\n";
		}
	}
	else
		cout << "Client with Account Number: (" << AccountNumber << ") Not found.\n";
}

void ShowMenueScreen()
{
	cout << "====================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "====================================================\n";
	cout << "\t[1] Show Client's List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client's Info.\n";
	cout << "\t[5] Find Clients.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "====================================================\n";
}

void ShowTransactionsMenueScreen()
{
	cout << "====================================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "====================================================\n";
	cout << "\t[1] Deposite.\n";
	cout << "\t[2] With Draw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "====================================================\n";
}

void BackToMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	system("cls");
	ShowMenueScreen();
}

void BackToTransactionsMenue()
{
	cout << "\n\nPress any key to go back to Transactions Main Menue...";
	system("pause>0");
	system("cls");
	ShowTransactionsMenueScreen();
}

void Deposite()
{
	vector<sClient> Clients = ConvertDataFromFileToRecord();
	sClient Client;
	string AccountNumber;
	double Amount = 0;
	char sure = 'n';

	cout << "Enter the Account Number:\n";
	cin >> AccountNumber;

	while (!(SearchByAccountNumber(AccountNumber, Clients, Client)))
	{
		cout << "Client With Account Number [" << AccountNumber << "] Does Not Exist, Enter another:\n";
		cin >> AccountNumber;
	}

	PrintClientRecord(Client);
	cout << "\n\nEnter Deposit Amount:\n";
	cin >> Amount;
	cout << "Are you sure you want to perform this transaction? (Y/N)\n";
	cin >> sure;

	if (sure == 'y' || sure == 'Y')
	{

		for (sClient& C : Clients)
		{
			if (C.AccountNumber == Client.AccountNumber)
			{
				C.AccountBalance += Amount;
				break;
			}
		}


		fstream ClientFile("Client.txt", ios::out);
		if (ClientFile.is_open())
		{
			for (sClient C : Clients)
			{
				ClientFile << ConvertRecordToLine(C) << endl;
			}
			ClientFile.close();
		}

		cout << "Deposit completed successfully.\n";
	}
}

void WithDraw()
{
	vector<sClient> Clients = ConvertDataFromFileToRecord();
	sClient Client;
	string AccountNumber;
	double Amount = 0;
	char sure = 'n';

	cout << "Enter the Account Number:\n";
	cin >> AccountNumber;

	while (!(SearchByAccountNumber(AccountNumber, Clients, Client)))
	{
		cout << "Client With Account Number [" << AccountNumber << "] Does Not Exist, Enter another:\n";
		cin >> AccountNumber;
	}

	PrintClientRecord(Client);
	cout << "\n\nEnter Withdrawal Amount:\n";
	cin >> Amount;

	if (Amount > Client.AccountBalance)
	{
		cout << "Insufficient funds!\n";
		return;
	}

	cout << "Are you sure you want to perform this transaction? (Y/N)\n";
	cin >> sure;

	if (sure == 'y' || sure == 'Y')
	{

		for (sClient& C : Clients)
		{
			if (C.AccountNumber == Client.AccountNumber)
			{
				C.AccountBalance -= Amount;
				break;
			}
		}


		fstream ClientFile("Client.txt", ios::out);
		if (ClientFile.is_open())
		{
			for (sClient C : Clients)
			{
				ClientFile << ConvertRecordToLine(C) << endl;
			}
			ClientFile.close();
		}

		cout << "Withdrawal completed successfully.\n";
	}
}

double CalculateTotalBalances(vector <sClient> Clients)
{
	double sumBalance = 0;
	for (sClient C : Clients)
	{
		sumBalance += C.AccountBalance;
	}
	return sumBalance;
}

void ShowTotalBalances()
{
	vector <sClient> Clients = ConvertDataFromFileToRecord();
	double sumBalance = CalculateTotalBalances(Clients);
	PrintTransactionsList(Clients);
	cout << "\n\n\t\t\tTotal Balances = " << sumBalance << endl;
}

void DepositeScreen()
{
	cout << "\n---------------------------------\n";
	cout << "\tDeposite Screen :-)\n";
	cout << "---------------------------------\n";
	Deposite();
}

void WithDrawScreen()
{
	cout << "\n---------------------------------\n";
	cout << "\tWithDraw Screen :-)\n";
	cout << "---------------------------------\n";
	WithDraw();
}

string ConvertRecordToLineForUsers(sUsers User, string seperator = "#//#")
{
	string stString = "";

	stString += User.UserName + seperator;
	stString += User.Password + seperator;
	stString += User.Permission;

	return stString;
}

void SaveUsersToFile(sUsers User)
{
	fstream UsersFile;
	string stData;

	UsersFile.open("Users.txt", ios::out | ios::app);
	if (UsersFile.is_open())
	{
		stData = ConvertRecordToLineForUsers(User);
		UsersFile << stData << endl;
	}
	UsersFile.close();
}

void ChooseTransactionsMenueChoice()
{
	enTransactionsChoices TransactionsChoices;
	vector <sClient> Clients = ConvertDataFromFileToRecord();
	string AccountNumber = "";
	sClient Client;

	short Choice;
	ShowTransactionsMenueScreen();
	cout << "Choose What Do You Want To Do? [1-4].\n";
	cin >> Choice;

	switch (Choice)
	{
	case enTransactionsChoices::enDeposite:
	{
		system("cls");
		DepositeScreen();
		BackToTransactionsMenue();
		break;
	}
	case enTransactionsChoices::enWithDraw:
	{
		system("cls");
		WithDrawScreen();
		BackToTransactionsMenue();
		break;
	}
	case enTransactionsChoices::enTotalBalances:
	{
		system("cls");
		ShowTotalBalances();
		BackToTransactionsMenue();
		break;
	}
	case enTransactionsChoices::enMainMenue:
	{
		system("cls");
		BackToMenue();
		break;
	}

	}

}

sUsers ConvertLineToRecordForUsers(string line, string seperator = "#//#")
{
	vector <string> vString;
	sUsers User;

	vString = Split(line, seperator);

	User.UserName = vString[0];
	User.Password = vString[1];
	User.Permission = stoi(vString[2]);

	return User;
}

vector <sUsers> ConvertDataFromFileToRecordForUsers()
{
	vector <sUsers> Users;

	string line = "";
	fstream UsersFile;

	UsersFile.open("Users.txt", ios::in);

	while (getline(UsersFile, line))
	{
		sUsers User;

		User = ConvertLineToRecordForUsers(line);
		Users.push_back(User);
	}
	UsersFile.close();

	return Users;
}

void LoginScreen()
{
	cout << "\n---------------------------------\n";
	cout << "\tLogin Screen :-)\n";
	cout << "---------------------------------\n";

}

bool IsItUsername(vector <sUsers>& Users, string Username, sUsers& User)
{

	for (sUsers U : Users)
	{
		if (U.UserName == Username)
		{
			User = U;
			return true;
		}
	}
	return false;
}

void ManageUsersMenueScreen()
{
	cout << "====================================================\n";
	cout << "\t\tManage Users Menue Screen\n";
	cout << "====================================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User's Info.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "====================================================\n";
}

void BackToManageUsers()
{
	cout << "\n\nPress any key to go back to Manage Screen...";
	system("pause>0");
	system("cls");
	ManageUsersMenueScreen();
}

void PrintUsersRecordForTable(sUsers User)
{
	cout << "| " << left << setw(30) << User.UserName;
	cout << "| " << left << setw(15) << User.Password;
	cout << "| " << left << setw(10) << User.Permission;
}

void PrintUsersList(vector <sUsers>& Users)
{
	cout << "\n\n\t\t\t\t\tUsers List (" << Users.size() << ") User(s)\n";
	cout << "\n____________________________________________________________________________________";
	cout << "______________________\n\n";
	cout << "| " << left << setw(30) << "Username ";
	cout << "| " << left << setw(15) << "Password ";
	cout << "| " << left << setw(10) << "Permission ";
	cout << "\n____________________________________________________________________________________";
	cout << "______________________\n\n";

	for (sUsers U : Users)
	{
		PrintUsersRecordForTable(U);
		cout << endl;
	}
}

int CheckPermission()
{
	int Permission = 0;
	char Answer;

	cout << "Show Client List? (Y/N) ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enUserPermission::pShowList;
	}
	cout << "Add New Client? (Y/N) ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enUserPermission::pAddClient;
	}
	cout << "Delete Client? (Y/N) ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enUserPermission::pDeleteClient;
	}
	cout << "Update Client? (Y/N) ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enUserPermission::pUpdateClient;
	}
	cout << "Find Client? (Y/N) ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enUserPermission::pFindClient;
	}
	cout << "Tranactions? (Y/N) ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enUserPermission::pTransactions;
	}
	cout << "Manage Users? (Y/N) ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enUserPermission::pManageUsers;
	}

	return Permission;
}

sUsers ReadNewUser()
{
	sUsers User;
	vector <sUsers> Users = ConvertDataFromFileToRecordForUsers();

	cout << "Enter Username ? ";
	getline(cin >> ws, User.UserName);

	while (IsItUsername(Users, User.UserName, User))
	{
		cout << "User [" << User.UserName << "]is already exist, Enter another.\n";
		getline(cin >> ws, User.UserName);
	}
	cout << "Enter password? ";
	getline(cin, User.Password);

	char Answer;
	cout << "Do You want to give him full permission (Y/N)? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		User.Permission = -1;
	}
	else
	{
		User.Permission = CheckPermission();
	}

	Users = ConvertDataFromFileToRecordForUsers();

	return User;
}

void AddNewUser()
{
	char Add = 'Y';
	sUsers User;

	while (Add == 'Y' || Add == 'y')
	{
		User = ReadNewUser();
		SaveUsersToFile(User);
		cout << "\n\nUser Added Successfully, do you want to addmore Users? (Y / N) ";
		cin >> Add;
	}
}

void DeniedScreen()//                                                                                                                                                                                           
{
	cout << "\n---------------------------------\n";
	cout << "\tPremission Denied :-)\n";
	cout << "---------------------------------\n";
	BackToMenue();
}

void LogoutScreen()
{
	cout << "\n---------------------------------\n";
	cout << "\tLogout Screen :-)\n";
	cout << "---------------------------------\n";

}

void PrintUserInfo(sUsers User)
{
	cout << "The following are the User's details\n\n";

	cout << "Username:   " << User.UserName << endl;
	cout << "Password:   " << User.Password << endl;
	cout << "Permission: " << User.Permission << endl;
}

void MarkToDeleteUseres(string Username, vector <sUsers>& Users, sUsers& User)
{
	for (sUsers& U : Users)
	{
		if (U.UserName == Username)
		{
			User = U;
			U.MarkDelete = true;
		}
	}
}

void SaveUsersAfterDeletedToFile(vector <sUsers>& Users, sUsers& User)
{
	fstream UsersFile;
	string UsersInfo;
	UsersFile.open("Users.txt", ios::out);

	if (UsersFile.is_open())
	{
		for (sUsers U : Users)
		{
			if (U.MarkDelete == false)
			{
				UsersInfo = ConvertRecordToLineForUsers(U);
				UsersFile << UsersInfo << endl;
			}
		}
		UsersFile.close();
	}
}

void DeleteUsersFromRecord(string Username, vector <sUsers>& Users)
{
	sUsers User;
	char sure = 'n';

	if (IsItUsername(Users, Username, User))
	{
		PrintUserInfo(User);

		cout << "\n\nAre you sure you want to delete this User? Y/N ";
		cin >> sure;

		if (sure == 'Y' || sure == 'y')
		{
			MarkToDeleteUseres(Username, Users, User);
			SaveUsersAfterDeletedToFile(Users, User);

			Users = ConvertDataFromFileToRecordForUsers();

			cout << "User's Deleted Successfuly.\n";
		}
	}
	else
		cout << "Client with Username: (" << Username << ") Not found.\n";
}

void UpdateUserRecord(string Username, vector <sUsers>& Users)
{
	sUsers User;
	char sure = 'n';

	if (IsItUsername(Users, Username, User))
	{
		PrintUserInfo(User);

		cout << "\n\nAre you sure you want to Update this User? Y/N ";
		cin >> sure;

		if (sure == 'Y' || sure == 'y')
		{
			MarkToDeleteUseres(Username, Users, User);
			SaveUsersAfterDeletedToFile(Users, User);

			Users = ConvertDataFromFileToRecordForUsers();

			User = ReadNewUser();

			SaveUsersToFile(User);

			cout << "\nUser's Updated Successfuly.\n";
		}
	}
	else
		cout << "Client with Account Number: (" << Username << ") Not found.\n";
}

sCurrentUser ReadCurrentUser()
{
	sCurrentUser CurrentUser;

	cout << "Enter Username? ";
	cin >> CurrentUser.UserName;
	cout << "Enter Password? ";
	cin >> CurrentUser.Password;

	return CurrentUser;
}

bool CheckAccessPermission(enUserPermission Permission, sCurrentUser CurrentUser)
{
	if (CurrentUser.Permission == enUserPermission::pAll)
		return true;

	return (CurrentUser.Permission & Permission) == Permission;//??? ???????
}

bool CheckUsernameAndPassword(sCurrentUser CurrentUser, vector<sUsers>& Users, sUsers& User)
{
	for (sUsers U : Users)
	{
		if (U.UserName == CurrentUser.UserName && U.Password == CurrentUser.Password)
		{
			User = U;
			return true;
		}
	}
	return false;
}

void ChooseManageUsers()
{
	ManageUsersMenue MenueChoice;
	vector <sUsers> Users = ConvertDataFromFileToRecordForUsers();
	string Username = "";
	sUsers User;

	short Choice;
	ManageUsersMenueScreen();
	cout << "Choose What Do You Want To Do? [1-6].\n";
	cin >> Choice;

	switch (Choice)
	{
	case ManageUsersMenue::enListUser:
	{
		system("cls");
		PrintUsersList(Users);
		BackToManageUsers();
		break;
	}
	case ManageUsersMenue::enAddNewUser:
	{
		system("cls");
		AddNewUser();
		BackToManageUsers();
		break;
	}
	case ManageUsersMenue::enDeleteUser:
	{
		system("cls");
		cout << "Enter the Username:\n";
		cin >> Username;
		DeleteUsersFromRecord(Username, Users);
		BackToManageUsers();
		break;
	}
	case ManageUsersMenue::enUpdateUser:
	{
		system("cls");
		cout << "Enter the Username:\n";
		cin >> Username;
		UpdateUserRecord(Username, Users);
		BackToManageUsers();
		break;
	}
	case ManageUsersMenue::enFindUser:
	{
		system("cls");
		cout << "Enter the Username:\n";
		cin >> Username;
		if (IsItUsername(Users, Username, User))
		{
			PrintUserInfo(User);
			BackToManageUsers();
		}
		else
		{
			cout << "Username [" << Username << "] Not found.\n";
			BackToManageUsers();
		}
		break;
	}
	case ManageUsersMenue::enuMainMenue:
	{
		system("cls");
		BackToMenue();
		break;
	}
	}
}

void ChooseMeneuChoice(sCurrentUser CurrentUser)
{
	while (true)
	{
		enMenueChoices MenueChoices;
		vector <sClient> Clients = ConvertDataFromFileToRecord();
		string AccountNumber = "";
		sClient Client;

		short Choice;
		ShowMenueScreen();
		cout << "Choose What Do You Want To Do? [1-8].\n";
		cin >> Choice;

		switch (Choice)
		{
		case enMenueChoices::enShowClientList:
		{
			if (CheckAccessPermission(pShowList, CurrentUser))
			{
				system("cls");
				PrintClientsList(Clients);
				BackToMenue();
				break;
			}
			else
				DeniedScreen();
		}
		case enMenueChoices::enAddNewClient:
		{
			if (CheckAccessPermission(pAddClient, CurrentUser))
			{
				system("cls");
				AddNewClientScreen();
				ReadNewClient();
				BackToMenue();
				break;
			}
			else
				DeniedScreen();
		}
		case enMenueChoices::enDleteClient:
		{
			if (CheckAccessPermission(pDeleteClient, CurrentUser))
			{
				system("cls");
				cout << "Enter the Account Number:\n";
				cin >> AccountNumber;
				DeleteClientFromRecord(AccountNumber, Clients);
				BackToMenue();
				break;
			}
			else
				DeniedScreen();
		}
		case enMenueChoices::enUpdateClientInfo:
		{
			if (CheckAccessPermission(pUpdateClient, CurrentUser))
			{
				system("cls");
				cout << "Enter the Account Number:\n";
				cin >> AccountNumber;
				UpdateClientRecord(AccountNumber, Clients);
				BackToMenue();
				break;
			}
			else
				DeniedScreen();
		}
		case enMenueChoices::enFindClient:
		{
			if (CheckAccessPermission(pFindClient, CurrentUser))
			{
				system("cls");
				cout << "Enter the Account Number:\n";
				cin >> AccountNumber;
				if (SearchByAccountNumber(AccountNumber, Clients, Client))
				{
					PrintClientRecord(Client);
					BackToMenue();
				}
				else
				{
					cout << "Account Number [" << AccountNumber << "] Not found.\n";
					BackToMenue();
				}

				break;
			}
			else
				DeniedScreen();
		}
		case enMenueChoices::enTransactions:
		{
			if (CheckAccessPermission(pTransactions, CurrentUser))
			{
				system("cls");
				ChooseTransactionsMenueChoice();
				break;
			}
			else
				DeniedScreen();
		}
		case enMenueChoices::enManageUsers:
		{
			if (CheckAccessPermission(pManageUsers, CurrentUser))
			{
				system("cls");
				ChooseManageUsers();
				break;
			}
			else
				DeniedScreen();
		}
		case enMenueChoices::enLogout:
		{
			system("cls");
			LogoutScreen();
			exit(0);
			break;
		}

		}
		system("cls");
	}
}

void Login()
{
	LoginScreen();
	sCurrentUser CurrentUser;
	sUsers User;
	vector <sUsers> Users = ConvertDataFromFileToRecordForUsers();

	CurrentUser = ReadCurrentUser();
	while (!(CheckUsernameAndPassword(CurrentUser, Users, User)))
	{
		cout << "Invalid Username/Password\n";
		CurrentUser = ReadCurrentUser();
	}
	CurrentUser.Permission = User.Permission;
	system("cls");
	ChooseMeneuChoice(CurrentUser);
}





int main()
{

	Login();






	return 0;
}
















