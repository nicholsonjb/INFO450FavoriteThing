// INFO450FavoriteThing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
const int ARRAYSIZE = 100;

class inventoryBeer
{
	string beerNumber;
	string beerName;
	string beerBrewery;
	string alocholContent;
	string beerRating;
	

public:
	inventoryBeer();
	inventoryBeer(string num, string name, string brewer, string rate, string alc);
	void captureInventoryBeer();
	void showInventoryBeer();
	int saveInventoryBeer(ofstream& outfile);
};

class inventoryBeerList
{
	inventoryBeerList** list;
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




int main()
{
    return 0;
}

