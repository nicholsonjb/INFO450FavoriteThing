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

//Beer  Class
class Beer
{
	string beerName;
	string beerStyle;
	string alocholContent;
	string beerBrewery;
	string beerLocation;
	string beerRating;


public:
	Beer();
	Beer(string name, string style, string alc, string brewer, string loc, string rate);
	void captureBeerItem();
	void showBeerItem();
	int saveBeerItem(ofstream& outfile);
	
};

//Beer  List Class

class BeerList
{
	Beer** list;
	int numrecords;
	int listsize;
	int reallocateArray();
public:
	BeerList();
	~BeerList();
	void getUserInput();
	void showBeerList();
	int saveBeerList(string filename);
	int readBeerList(string filename);
	int duplicateBeerItem(string name, string brewer); //this checks for duplicates by name
};


//default constructor - intialized empty
Beer::Beer()
{
	beerName = "";
	beerStyle = "";
	alocholContent = "";
	beerBrewery = "";
	beerLocation = "";
	beerRating = "";
}

//overload constructor intilaized with values
Beer::Beer(string name, string style, string alc, string brewer, string loc, string rate)
{
	beerName = name;
	beerStyle = style;
	alocholContent = alc;
	beerBrewery = brewer;
	beerLocation = loc;
	beerRating = rate;
}

//Capture beer from end users
void Beer::captureBeerItem()
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
}

//Display beer to console
void Beer::showBeerItem()
{
	cout << "-----------------------\n";
	cout << "Name: " << beerName << "\nBeer Style: " << beerStyle << "\nABV: " << alocholContent
		<< "\nBrewery: " << beerBrewery << "\nLocation: " << beerLocation << "\nRating: " << beerRating << endl;
}


//Save beer item to given input file stream
int Beer::saveBeerItem(ofstream& outfile)
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

//Beer  List Constructor - allocate space for the array
BeerList::BeerList()
{
	list = new Beer*[ARRAYSIZE];
	numrecords = 0;
	listsize = ARRAYSIZE;
}

//Deconstructor - free allocated memeory
BeerList::~BeerList()
{
	for (int i = 0; i < numrecords; i++)
	{
		delete list[i];
	}
	delete[]list;
}

//Reallocate memory if already at capacity
int BeerList::reallocateArray()
{
	Beer** temp;
	temp = new Beer*[listsize + ARRAYSIZE];
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
void BeerList::getUserInput()
{
	string answer = "Y";
	cout << "Enter item Y/N" << endl;
	getline(cin, answer);
	while (answer == "Y" || answer == "y")
	{
		list[numrecords] = new Beer();
		list[numrecords]->captureBeerItem();
		numrecords++;
		cout << "Enter another item Y/N" << endl;
		getline(cin, answer);
	}
}

//Show beer list to console
void BeerList::showBeerList()
{
	for (int i = 0; i < numrecords; i++)
	{
		list[i]->showBeerItem();
	}
}


//Save list to file
int BeerList::saveBeerList(string filename)
{
	ofstream output(filename, ios::trunc);
	if (output)
	{
		for (int i = 0; i < numrecords; i++)
		{
			list[i]->saveBeerItem(output);
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
int BeerList::readBeerList(string filename)
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
			list[numrecords] = new Beer(iname, istyle, ialc, ibrew, iloc, irate);
			numrecords++;
		}
	}
	infile.close();
	return 0;
}







int main()
{
	BeerList my;

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
	my.getUserInput();
	my.saveBeerList(filename);
	my.showBeerList();
	return 0;
}
