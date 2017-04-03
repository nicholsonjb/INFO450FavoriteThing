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
	string beerRating;
	string alocholContent;

public:
	inventoryBeer();
	inventoryBeer(string num, string name, string brewer, string rate, string alc);
	void CaptureInventoryBeer();
	void ShowInventoryBeer();
	int SaveInventoryBeer(ofstream& outfile);
};

class inventoryBeerList
{
	
};
int main()
{
    return 0;
}

