#pragma once
#include <string>
#include <vector>
#include <set>
using namespace std;
class Hash {
private:
	static const int tableSize = 1000;

	struct Image {
		string imageName;
		string imageColour;
		string imageType;
		int imageStock;
		double imagePrice;
		int imageDiscount;
		Image* next;
	};
	Image* HashTable[tableSize];
public:
	Hash();
	int hash(string key);

	vector<string> stringParser(string stringName);

	vector<Image*> searchImageByTag(vector<string> searchInput);
	Image* searchImageByName(string searchInput);
	void addImage(string imageName, string imageColour, string imageType, int imageStock, double imagePrice, int imageDiscount);
	void deleteImage(string name);

	void setPrice(double priceTag, string name);
	void setDiscount(int discountPercentage, string name);
	void setStock(int imageStock, string name);

	double getPrice(string name);
	int getDiscount(string name);
	int getStock(string name);

	friend void operator<<(ostream& stream, Image* image);
};

