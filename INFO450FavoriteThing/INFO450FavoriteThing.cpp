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
	inventoryBeer(string name, string style, string alc, string brewer, string loc, string rate );
	void captureInventoryBeerItem();
	void showInventoryBeerItem();
	int saveInventoryBeerItem(ofstream& outfile);
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
	int captureNewInventoryBeerItem();
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
inventoryBeer::inventoryBeer(std::string name, std::string style, std::string alc, std::string brewer, std::string loc, std::string rate)
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
	cout << "Beer Name --";
	getline(cin, beerName);
	cout << "Beer Style --";
	getline(cin, beerStyle);
	cout << "ABV --";
	getline(cin, alocholContent);
	cout << "Beer Brewery --";
	getline(cin, beerBrewery);
	cout << "Beer Location --";
	getline(cin, beerLocation);
	cout << "Beer Rating --";
	getline(cin, beerRating);
}

//Display beer to console
void inventoryBeer::showInventoryBeerItem()
{
	cout << "Name : " << beerName << " Beer Style : " << beerStyle << "ABV : " << alocholContent
		<< "Brewery : " << beerBrewery << "Location : " << beerLocation << "Rating : " << beerRating << endl;
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





int main()
{
    return 0;
}

