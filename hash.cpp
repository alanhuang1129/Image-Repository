#include "hash.h"
#include <iostream>
#include <set>
#include <iterator>
#include <iomanip> //setw
using namespace std;

Hash::Hash() {
	for (int i = 0; i < tableSize; i++) {
		HashTable[i] = new Image;
		HashTable[i]->imageName = "NA";
		HashTable[i]->imageColour = "NA";
		HashTable[i]->imageType = "NA";
		HashTable[i]->imageStock = 0;
		HashTable[i]->imagePrice = 0.0;
		HashTable[i]->imageDiscount = 0;
		HashTable[i]->next = NULL;
	}
}
int Hash::hash(string key) {
	int hash = 0;
	int index;

	index = key.length();
	//Simple hash function
	for (int i = 0; i < key.length(); i++) {
		hash += (int)key[i];
	}
	index = hash % tableSize;
	return index;
}

vector<string> Hash::stringParser(string stringName) {
	vector<string> stringVector;
	string tempString = "";
	int characterCounter = 0;
	int j, k = 0;
	int stringSize = stringName.size();
	for (int i = 0; i < stringSize; i++) {
		characterCounter++;
		if (stringName[i] == ' ') {
			//For loop for constructing a word into a temp string variable
			for (j = k;  j < characterCounter++; j++) {
				tempString += stringName[j];
			}
			k = j + 1; //fixes position to start of next word
			stringVector.push_back(tempString);
			tempString = "";
			characterCounter = 0;
		}
	}
	return stringVector;
}
//Function goes with StringParser
vector<Hash::Image*> Hash::searchImageByTag(vector<string> searchInput) {
	//Set used to avoid overlaps
	set<Image*> imagePtrSet;
	vector<Image*> returnVector;
	Image* Ptr;
	for (int i = 0; i < searchInput.size(); i++) {
		for (int traverse = 0; traverse < tableSize; traverse++) {
			if (HashTable[traverse]->imageName != "NA") { //If == "NA", it will traverse with no checks
				Ptr = HashTable[traverse];
				while (Ptr != NULL) {
					//Check for matching tags
					if (searchInput[i] == HashTable[traverse]->imageName) {
						imagePtrSet.insert(HashTable[traverse]);
					}
					if (searchInput[i] == HashTable[traverse]->imageColour) {
						imagePtrSet.insert(HashTable[traverse]);
					}
					if (searchInput[i] == HashTable[traverse]->imageType) {
						imagePtrSet.insert(HashTable[traverse]);
					}
					Ptr = Ptr->next;//go to next node
				}
				
			}
		}
	}
	for (set<Image*>::iterator itr = imagePtrSet.begin(); itr != imagePtrSet.end(); itr++) {
		returnVector.push_back(*itr);
	}
	if (returnVector[0] == NULL) //Check if empty
		cout << "\nThere were no matches\n";
	return returnVector;
}
Hash::Image* Hash::searchImageByName(string searchInput) {
	//Goes through each individual word in the string vector
	Image* Ptr;
	for (int traverse = 0; traverse < tableSize; traverse++) {
		if (HashTable[traverse]->imageName != "NA") {
			Ptr = HashTable[traverse];
			while (Ptr != NULL) {
				if (searchInput == HashTable[traverse]->imageName)
					return HashTable[traverse];
				Ptr = Ptr->next;
			}
		}
		if (traverse == tableSize - 1) {
			cout << "\nThe image you are looking for is not in the repository\n";
			return NULL;
		}
	}
}
void Hash::addImage(string imageName, string imageColour, string imageType, int imageStock, double imagePrice, int imageDiscount) {
	//Index is hashed by image type in order to categorize images
	int index = hash(imageType);
	//This block of code is necessary in the case the index is empty and a new node is not needed
	if (HashTable[index]->imageName == "NA") {
		HashTable[index]->imageName = imageName;
		HashTable[index]->imageColour = imageColour;
		HashTable[index]->imageType = imageType;
		HashTable[index]->imageStock = imageStock;
		HashTable[index]->imagePrice = imagePrice;
		HashTable[index]->imageDiscount = imageDiscount;
		HashTable[index]->next = NULL;
	}
	else {
		//Create a new node and place it at the end of the list
		Image* Ptr = HashTable[index];
		Image* newNode = new Image;
		HashTable[index]->next = newNode;
		newNode->imageName = imageName;
		newNode->imageColour = imageColour;
		newNode->imageType = imageType;
		newNode->imageStock = imageStock;
		newNode->imagePrice = imagePrice;
		newNode->imageDiscount = imageDiscount;
		newNode->next = NULL;
		while (Ptr->next != NULL) {
			Ptr = Ptr->next;
		}
		Ptr->next = newNode;
	}
}
void Hash::deleteImage(string name) {
	int bucket;
	int chainTarget = 1;
	//If the image is not in the repository
	Image* target = searchImageByName(name);
	if (target == NULL)
		return;
	bucket = hash(target->imageType);
	Image* tempPtr = HashTable[bucket];
	Image* tempPtr2 = HashTable[bucket];
	while (tempPtr->next != target) {
		//Error check
		if (tempPtr->next == NULL) {
			cout << "\nImage deleted\n";
			return;
		}
		tempPtr = tempPtr->next;
		chainTarget++;
	}
	for (int traverse2 = 0; traverse2 < chainTarget - 1; traverse2++) {
		tempPtr2 = tempPtr2->next;
	}
	tempPtr2->next = tempPtr->next;
	delete tempPtr2;
	cout << "\nImage has been deleted\n";
}

//Set Functions
void Hash::setPrice(double priceTag, string name) {
	Image* targetImage = searchImageByName(name);
	targetImage->imagePrice = priceTag;
}
void Hash::setDiscount(int discountPercentage, string name) {
	Image* targetImage = searchImageByName(name);
	targetImage->imageDiscount = discountPercentage;
}
void Hash::setStock(int imageStock, string name) {
	Image* targetImage = searchImageByName(name);
	targetImage->imageStock = imageStock;
}

//Get Functions
double Hash::getPrice(string name) {
	Image* targetImage = searchImageByName(name);
	return targetImage->imagePrice;
}
int Hash::getDiscount(string name) {
	Image* targetImage = searchImageByName(name);
	return targetImage->imageDiscount;
}
int Hash::getStock(string name) {
	Image* targetImage = searchImageByName(name);
	return targetImage->imageStock;
}

void operator<<(ostream& stream, Hash::Image* image) {
	stream << left << setw(20) << image->imageName
		<< setw(7) << "| Colour: " << image->imageColour
		<< left << setw(7) << " Type: " << image->imageType
		<< setw(7) << " Stock: " << image->imageStock
		<< setw(7) << " Price: " << image->imagePrice
		<< setw(7) << " Discount: " << image->imageDiscount
		<< endl << endl;
}