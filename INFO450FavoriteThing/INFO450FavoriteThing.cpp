// INFO450FavoriteThing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>

using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
const int ARRAYSIZE = 100;

//Beer Inventory Class
class inventoryBeer
{
	string beerName;
	string beerStyle;
	string alocholContent;
	string beerBrewery;
	string beerLocation;
	string beerRating;


public:
	inventoryBeer();
	inventoryBeer(string name, string style, string alc, string brewer, string loc, string rate);
	void captureInventoryBeerItem();
	void showInventoryBeerItem();
	int saveInventoryBeerItem(ofstream& outfile);
	void duplicateInventoryBeerItem(); //this checks for duplicates by name
	
};

//Beer Inventory List Class

class inventoryBeerList
{
	inventoryBeer** list;
	int numrecords;
	int listsize;
	int reallocateArray();
public:
	inventoryBeerList();
	~inventoryBeerList();
	void getUserInput();
	void showInventoryBeerList();
	int saveInventoryBeerList(string filename);
	int readInventoryBeerList(string filename);
	
	
};


//default constructor - intialized empty
inventoryBeer::inventoryBeer()
{
	beerName = "";
	beerStyle = "";
	alocholContent = "";
	beerBrewery = "";
	beerLocation = "";
	beerRating = "";
}

//overload constructor intilaized with values
inventoryBeer::inventoryBeer(string name, string style, string alc, string brewer, string loc, string rate)
{
	beerName = name;
	beerStyle = style;
	alocholContent = alc;
	beerBrewery = brewer;
	beerLocation = loc;
	beerRating = rate;
}

//Capture beer from end users
void inventoryBeer::captureInventoryBeerItem()
{
	cout << "Beer Name -->";
	getline(cin, beerName);
	cout << "Beer Style -->";
	getline(cin, beerStyle);
	cout << "ABV -->";
	getline(cin, alocholContent);
	cout << "Beer Brewery -->";
	getline(cin, beerBrewery);
	cout << "Beer Location -->";
	getline(cin, beerLocation);
	cout << "Beer Rating -->";
	getline(cin, beerRating);
	return 0;
}

//Display beer to console
void inventoryBeer::showInventoryBeerItem()
{
	cout << "-----------------------\n";
	cout << "Name: " << beerName << "\nBeer Style: " << beerStyle << "\nABV: " << alocholContent
		<< "\nBrewery: " << beerBrewery << "\nLocation: " << beerLocation << "\nRating: " << beerRating << endl;
}


//Save beer item to given input file stream
int inventoryBeer::saveInventoryBeerItem(ofstream& outfile)
{
	if (outfile.is_open())
	{
		outfile << beerName << "|" << beerStyle << "|" << alocholContent << "|" << beerBrewery << "|" << beerLocation << "|"
			<< beerRating << endl;
		return 0;
	}
	else
		return WRITEERROR;
}

//Beer inventory List Constructor - allocate space for the array
inventoryBeerList::inventoryBeerList()
{
	list = new inventoryBeer*[ARRAYSIZE];
	numrecords = 0;
	listsize = ARRAYSIZE;
}

//Deconstructor - free allocated memeory
inventoryBeerList::~inventoryBeerList()
{
	for (int i = 0; i < numrecords; i++)
	{
		delete list[i];
	}
	delete[]list;
}

//Reallocate memory if already at capacity
int inventoryBeerList::reallocateArray()
{
	inventoryBeer** temp;
	temp = new inventoryBeer*[listsize + ARRAYSIZE];
	listsize = listsize + ARRAYSIZE;
	for (int i = 0; i < numrecords; i++)
	{
		temp[i] = list[i];
	}
	delete[]list;
	list = temp;
	return 0;
}

//Get User Input --Will need addtional work
void inventoryBeerList::getUserInput()
{

	string ans = "Y";
	inventoryBeer *myBeer;
	myBeer = new inventoryBeer;
	myBeer->captureInventoryBeerItem();

	cout << "Enter Beer Y/N?" << endl;
	getline(cin, ans);
	

	while (ans == "y" || ans == "Y")
	{
		if (!myBeer->duplicateInventoryBeerItem())
		{
			
		}
		else
		{
			list[numrecords] = new inventoryBeer();
			list[numrecords]->captureInventoryBeerItem();
			numrecords++;
			cout << "Enter another Beer? Y/N?" << endl;
			getline(cin, ans);
		}
	}
}

//Show beer list to console
void inventoryBeerList::showInventoryBeerList()
{
	for (int i = 0; i < numrecords; i++)
	{
		list[i]->showInventoryBeerItem();
	}
}


//Save list to file
int inventoryBeerList::saveInventoryBeerList(string filename)
{
	ofstream output(filename, ios::trunc);
	if (output)
	{
		for (int i = 0; i < numrecords; i++)
		{
			list[i]->saveInventoryBeerItem(output);
		}
		output.close();
	}
	else
	{
		return WRITEERROR;
	}

	return 0;
}

//Read beer list from a file
int inventoryBeerList::readInventoryBeerList(string filename)
{
	string iname, istyle, ialc, ibrew, iloc, irate;
	int count = 0;
	ifstream infile(filename, ios::in);
	if (!infile)
	{
		cout << "File could not be opened" << endl;
		return READERROR;
	}
	while (!infile.eof())
	{
		if (numrecords == listsize)
		{
			reallocateArray();
		}
		getline(infile, iname, '|');
		if (!iname.empty())
		{
			getline(infile, istyle, '|');
			getline(infile, ialc, '|');
			getline(infile, ibrew, '|');
			getline(infile, iloc, '|');
			getline(infile, irate);
			list[numrecords] = new inventoryBeer(iname, istyle, ialc, ibrew, iloc, irate);
			numrecords++;
		}
		
	}
	infile.close();
	return 0;
}

void inventoryBeer::duplicateInventoryBeerItem()
{
	if (beerName == beerName && beerBrewery == beerBrewery)
	{
		cout << "Duplicate beer found" << endl;
	}
}




int main()
{
	inventoryBeerList myInventory;

	string filename;
	cout << "Welcome to The Beer Club Craft Beer Tracker!" << endl;
	cout << "To access the list text file. Use the file path where the text file" << endl;
	cout << "is stored on your machine. Ex. C:\\Projects\\BrewList.txt" << endl;

	cout << "Enter the full path of the file: " << endl;
	getline(cin, filename);
	ifstream file(filename.c_str());

	if (!file)
	{
		cout << "Error while opening the file" << endl;
		return 1;
	}
	myInventory.getUserInput();
	myInventory.saveInventoryBeerList(filename);
	myInventory.showInventoryBeerList();
	return 0;
}


