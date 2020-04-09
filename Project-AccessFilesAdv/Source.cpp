//Rafael Ceotto
//3/28/2020
//Description: A menu-driven program that updates the binary inventory file, db.dat. 

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//Following Structure
const int DESC_SIZE = 40;
struct Product
{
	char prodName[DESC_SIZE];
	long prodNum;
	int qty;
	double price;
	
};

//Prototype
int showMenu();
void addRecord(fstream&);
void viewRecord(fstream&);
void editRecord(fstream&);


int main()
{
	long choice;
	fstream fileDB;
	
	do
	{
		choice = showMenu();
		switch (choice)
		{
		case 1:       
			addRecord(fileDB);
			break;
		case 2:       
			viewRecord(fileDB);
			break;
		case 3:      
			editRecord(fileDB);
			break;

		case 4:
			break;
			

		default:            
			cout << "Wrong choice" << endl;
		}

	} while (choice != 4);


	
	fileDB.close();

	system("pause");
	return 0;
}



int showMenu()
{
	int choice;
	
	
	cout << "Inventory menu " << "\n";
	cout << "1 - Enter a product" << "\n";
	cout << "2 - Display a particular record" << "\n";
	cout << "3 - Modify product" << "\n";
	cout << "4 - Terminate Program" << "\n\n";
	
	cout << "Enter your choice: " << "\n";
	cin >> choice;

	while (choice < 1 || choice > 4)
	{
		cout << "Wrong selection. Try Again ";
		cin >> choice;
	}

	
	cout << "\n";

	return choice;
}


void addRecord(fstream& file)
{

	file.open("db.dat", ios::out | ios::binary | ios::app);
	Product field;
	cout << "Enter the number of the product: ";
	cin >> field.prodNum;
	cout << "Record # " << field.prodNum << " ";
	cout << "Product Name: ";
	cin.ignore();
	cin.getline(field.prodName, 20);
	
	

	do
	{
		cout << "Quantity: ";
		cin >> field.qty;

		if (field.qty < 0)
			cout << "Invalid quantity " << endl;

	} while (field.qty < 0);

	do
	{
		cout << "Price: $";
		cin >> field.price;
		cout << "\n";

		if (field.price < 0)
			cout << "Invalid price " << endl;

	} while (field.price < 0);
	
	file.write((char*)(&field), sizeof(Product));
	file.close();
}

void viewRecord(fstream& file)
{

	file.open("db.dat", ios::in | ios::binary);
	Product field;
	cin.clear();
	cout << "Enter the record number of the item to view:";
	cin >> field.prodNum;

	file.seekp((field.prodNum - 1) * sizeof(field), ios::beg);
	file.read((char*)(&field), sizeof(Product));

	cout << "Description: " << field.prodName << endl;
	cout << "Quantity: " << field.qty << endl;
	cout << "Price: " << field.price << endl;
	cout << endl;

	file.close();
}


void editRecord(fstream& file)
{

	file.open("db.dat", ios::in | ios::binary);
	Product field;


	fflush(stdin);
	cout << "Enter the record number of the item you want to edit: ";
	cin >> field.prodNum;

	
	file.seekg((field.prodNum) * sizeof(Product), ios::beg);
	file.read((char*)(&field), sizeof(Product));

	cout << "Description: " << field.prodName << endl;
	cout << "Quantity: " << field.qty << endl;
	cout << "Price: " << field.price << endl;
	cout << endl;

	
	file.close();

	cout << "Description: ";
	cin.ignore();
	cin.getline(field.prodName, 20);
	
	do
	{
		cout << "Quantity: ";
		cin >> field.qty;

		if (field.qty < 0)
			cout << "Invalid quantity " << endl;

	} while (field.qty < 0);

	do
	{
		cout << "Price: ";
		cin >> field.price;

		if (field.price < 0)
			cout << "Invalid quantity " << endl;

	} while (field.price < 0);	

	
	file.open("db.dat", ios::out | ios::binary);
	
	file.seekg((field.prodNum - 1) * sizeof(Product), ios::beg);
	
	file.write((char*)(&field), sizeof(Product));

	file.close();
}