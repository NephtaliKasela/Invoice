#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
using namespace std;

struct Item
{
	string name;
	double price = 0;
};
struct item
{
	int unit;
	double price;
};
map<string, Item>  Items;
map<string, int> Order;

void ReadItems()
{
	ifstream f;
	f.open("1.ItemData.txt");
	f.ignore(255, '\n');
	f.ignore(255, '\n');
	Item item;
	while (!f.eof())
	{
		   string SKU;
		getline(f, SKU, '\t');
		getline(f, item.name, '\t');
		f >> item.price;
		f.ignore(255, '\n');
		Items[SKU] = item; //F0015
	}
	f.close();
}
void ReadOrder()
{
	ifstream file;
	file.open("1.Order.txt");
	for (int i = 0; i < 7; i++) file.ignore(255, '\n');
	while (!file.eof())
	{
		string key;
		int number;
		getline(file, key, '\t');
		file >> number;
		file.ignore(255, '\n');
		Order[key] = number;
	}
	file.close();
}
void Title()
{
	cout << setw(5) << "SKU" << setw(40) << "Item" << setw(12) << "Price" << endl;
	cout << setw(5) << "---------------------------------------------------------" << endl;
}
void invoiceTitle()
{
	cout << setw(40) << "Item" << setw(10) << "Units" << setw(12) << "Price" << endl;
	cout << setw(62) << "-------------------------------------------------------------" << endl;
}
void Head()
{
	cout << "Ship to:\n"; 
	cout << " Name   : Nephtali\n";
	cout << " Address: Pralietarskaya 16\n\n";
}
void ReadProducts(map <string, Item> Prod)
{
	map<string, Item>::iterator it;
	for (it = Prod.begin(); it != Prod.end(); it++)
	{
		cout << setw(5) << it->first << setw(40) << it->second.name << setw(12);
		cout << it->second.price << endl;
	}
}
double Discount(double subtotal)
{
	double discount { 0 };
	if (subtotal <= 100) discount = 0;
	if (subtotal >= 100.01 && subtotal <= 250) discount = (subtotal * 5) / 100;
	if (subtotal > 250)
	{
		discount = (subtotal * 5) / 100;
		discount = discount + (subtotal * 10) / 100;
	}
	return discount;
}
double SalesTax(double total)
{
	double saletax = (total * 4.5) / 100;
	return saletax;
}


int main()
{
	int command=0;
	while (command != 4)
	{
		system("cls");
		cout << "1. Print all products" << endl;
		cout << "2. Print the order" << endl;
		cout << "3. Print the invoice" << endl;
		cout << "4. Exit" << endl;
		cout << "Make your choice: ";
		cin >> command;

		cout << "---------------------\n" << endl;

		map<string, Item> found;
		set<string> unfound;
		map<string, int>::iterator it1;
		map<string, int>::iterator it3;

		switch (command)
		{
		case 1: //Print the content of map container
			ReadItems();
			Title();
			ReadProducts(Items);
			system("pause");
			break;
		case 2: //Print the content of map container
			ReadOrder();
			for (it1 = Order.begin(); it1 != Order.end(); it1++)
			{
				cout << setw(7) << it1->first << setw(8) << it1->second << endl;
			}
			system("pause");
			break;
		case 3: ReadItems();
			ReadOrder();
			Head();
			invoiceTitle();

			double Subtotal{ 0 };

			for (it3 = Order.begin(); it3 != Order.end(); it3++)
			{
				bool check = false;
				map<string, Item>::iterator it4;
				for (it4 = Items.begin(); it4 != Items.end(); it4++)
				{
					if (it3->first == it4->first)
					{
						Item item1 = Items[it4->first];
						found[it4->first] = item1;
						cout << setw(40) << item1.name << setw(10) << it3->second << setw(12) << item1.price * it3->second << endl;
						check = true;
						Subtotal = Subtotal + item1.price * it3->second;
						break;
					}
				}
				if (check == false) unfound.insert(it3->first);
			}
			//ReadProducts(found);
			cout << "--------------------------------------------------------------" << endl;
			double total = Subtotal - Discount(Subtotal);
			double saletax = SalesTax(total);
			cout << setw(50) << "Subtotal" << setw(12) << Subtotal << endl;
			cout << setw(50) << "Discount" << setw(12) << Discount(Subtotal) << endl;
			cout << setw(50) << "Sale tax" << setw(12) << SalesTax(total) << endl;
			cout << setw(50) << "Total" << setw(12) << total << endl << endl;
			cout << "  The following ordered items were not found:  " << endl;
			cout << "   ";
			copy(unfound.cbegin(), unfound.cend(), ostream_iterator <string>(cout, "   "));
			cout << endl;
			system("pause");
			break;
			//default: cout << "Try again..." << endl;
						//break;
		}

		//cout << "===================================" << endl;
		//Item item = Items["F0010"];
		//cout << item.name << " " << item.price << endl;
	}

	return 0;
}