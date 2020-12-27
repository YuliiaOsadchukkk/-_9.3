
#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <string>
#include <algorithm>
using namespace std;

struct Product 
{
	string name;
	string shop;
	float price; 
	int count;
	string od_vim; 
};

void drawProducts(Product** products, const int size)
{
	cout << "============================================================" << endl;
	cout << "| Name        | Shop         | Price | Count | Vimiruvanna |" << endl;
	cout << "============================================================" << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << "| " << setw(12) << products[i]->name
			<< "| " << setw(13) << products[i]->shop
			<< "| " << setw(6) << products[i]->price
			<< "| " << setw(6) << products[i]->count
			<< "| " << setw(12) << products[i]->od_vim
			<< "|" << endl;
		if (i != size - 1)
			cout << "------------------------------------------------------------" << endl;
	}
	cout << "============================================================" << endl;
}

Product** addProduct(Product** products, int& size, Product* product) 
{
	Product** prds = new Product * [++size];
	if (products != nullptr) 
	{
		memcpy(prds, products, sizeof(Product*) * (size - 1));
		delete[] products;
	}
	prds[size - 1] = product;
	return prds;
}

Product** removeProduct(Product** products, int& size, Product* product) 
{
	size_t i = 0;
	for (; i < size; i++)
		if (products[i] == product)
			break;
	if (i == size)
		return products;
	Product** prds = new Product * [--size];
	if (i > 0)
		memcpy(prds, products, sizeof(Product*) * i);
	if (i < size)
		memcpy(prds + i, products + i + 1, sizeof(Product*) * (size - i));
	delete[] products;
	return prds;
}

Product* selectProductByName(Product** products, const int size, const string name)
{
	for (size_t i = 0; i < size; i++)
		if (products[i]->name == name)
			return products[i];
	return nullptr;
}

Product** filterByPrice(Product** products, const int size, int& out_s, const float start, const float stop)
{
	Product** prds = nullptr;
	for (size_t i = 0; i < size; i++)
	{
		if (products[i]->price >= start && products[i]->price <= stop)
			prds = addProduct(prds, out_s, products[i]);
	}
	return prds;
}

Product** filterByShop(Product** products, const int size, int& out_s, const string shop) 
{
	Product** prds = nullptr;
	for (size_t i = 0; i < size; i++)
	{
		if (products[i]->shop == shop)
			prds = addProduct(prds, out_s, products[i]);
	}
	return prds;
}

void editProduct(Product* product)
{
	int state = 0;

	do
	{
		system("cls");
		cout << "Select editing property" << endl
			<< "[1] Name" << endl
			<< "[2] Shop" << endl
			<< "[3] Price" << endl
			<< "[4] Count" << endl
			<< "[5] Vimiruvanna" << endl
			<< "[0] Back" << endl;
		do {
			cin >> state;
		} while (cin.fail());
		if (state == 0)
			break;
		cout << "Input new property: ";
		bool is_valid = false;
		do
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			switch (state)
			{
			case 1:
				cin >> product->name;
				is_valid = true;
				break;
			case 2:
				cin >> product->shop;
				is_valid = true;
				break;
			case 3:
				cin >> product->price;
				if (product->price > 0)
					is_valid = true;
				break;
			case 4:
				cin >> product->count;
				if (product->count > 0)
					is_valid = true;
				break;
			case 5:
				cin >> product->od_vim;
				is_valid = true;
				break;
			}

		} while (!is_valid);
	} while (state != 0);
}

void sortByShop(Product** products, const int size) 
{
	for (int i = 0; i < size - 1; ++i)
		for (int j = 0; j < size - i - 1; ++j)
			if (products[j]->shop > products[j + 1]->shop)
				swap(products[j], products[j + 1]);
}

void sortByPrice(Product** products, const int size) 
{
	for (int i = 0; i < size - 1; ++i)
		for (int j = 0; j < size - i - 1; ++j)
			if (products[j]->price > products[j + 1]->price)
				swap(products[j], products[j + 1]);
}

Product* createProduct()
{
	Product* prd = new Product();
	cout << "__Creating product__ " << endl;
	cout << "Input name: "; cin >> prd->name;
	cout << "Input shop: "; cin >> prd->shop;
	cout << "Input price > 0: ";
	do
	{
		if (cin.fail())
		{
			cin.clear(); // очищаємо усы флаги вводу до good
			cin.ignore(INT_MAX, '\n'); // ігноруємо теперішню строку в буфері
		}
		cin >> prd->price;
	} while (cin.fail() || prd->price <= 0);
	cout << "Input count > 0: ";
	do
	{
		if (cin.fail()) 
		{
			cin.clear(); // очищаємо усы флаги вводу до good
			cin.ignore(INT_MAX, '\n'); // ігноруємо теперішню строку в буфері
		}
		cin >> prd->count;
	} while (cin.fail() || prd->price <= 0);
	cout << "Input od vim: "; cin >> prd->od_vim;
	return prd;
}

void main()
{
	Product** prds = nullptr;
	int size = 0;
	int state = 0;
	char msg[256] = { 0 };
	do
	{
		system("cls");
		drawProducts(prds, size);
		if (msg[0] != 0) {
			cout << msg << endl;
			msg[0] = 0;
		}
		cout << "Select editing property" << endl
			<< "[1] Edit product" << endl
			<< "[2] Sort by shop" << endl
			<< "[3] Sort by price" << endl
			<< "[4] Draw products from shop" << endl
			<< "[5] Draw products with price" << endl
			<< "[6] Add product" << endl
			<< "[7] Remove product" << endl
			<< "[0] Exit" << endl;
		cin >> state;
		if (cin.fail())
		{
			strcpy_s(msg, 255, "Incorrect operation!");
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			state = -1;
			continue;
		}
		switch (state) 
		{
		case 1: {
			string name;
			cout << "Input name of product: ";
			cin >> name;
			Product* prd = selectProductByName(prds, size, name);
			if (prd != nullptr)
				editProduct(prd);
			else strcpy_s(msg, 255, "Incorrect name of product!");
		}
			  break;
		case 2:
			sortByShop(prds, size);
			strcpy_s(msg, 255, "Sorted by shop!");
			break;
		case 3:
			sortByPrice(prds, size);
			strcpy_s(msg, 255, "Sorted by price!");
			break;
		case 4:
		{
			string name;
			cout << "Input name of shop: ";
			cin >> name;
			int out_size = 0;
			Product** pr = filterByShop(prds, size, out_size, name);
			if (pr != nullptr) 
			{
				drawProducts(pr, out_size);
				delete[] pr;
				system("pause");
			}
			else strcpy_s(msg, 255, "None products find!");
		}break;
		case 5:
		{
			float price[2];
			cout << "Input start of price: ";
			cin >> price[0];
			if (cin.fail() || price[0] <= 0)
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				strcpy_s(msg, 255, "Incorrect start of price!");
				break;
			}
			cout << "Input end of price: ";
			cin >> price[1];
			if (cin.fail() || price[1] < price[0])
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				strcpy_s(msg, 255, "Incorrect end of price!");
				break;
			}
			int out_size = 0;
			Product** pr = filterByPrice(prds, size, out_size, price[0], price[1]);
			if (pr != nullptr) 
			{
				drawProducts(pr, out_size);
				delete[] pr;
				system("pause");
			}
			else strcpy_s(msg, 255, "None products find!");
		}break;
		case 6:
			system("cls");
			prds = addProduct(prds, size, createProduct());
			strcpy_s(msg, 255, "Product added!");
			break;
		case 7:
		{
			string name;
			cout << "Input name of product: ";
			cin >> name;
			Product* prd = selectProductByName(prds, size, name);
			if (prd != nullptr)
				prds = removeProduct(prds, size, prd);
			else strcpy_s(msg, 255, "Incorrect name of product!");
		}
		break;
		case 0:
			break;
		default:
			strcpy_s(msg, 255, "Incorrect operation!");
		}
	} while (state != 0);
}