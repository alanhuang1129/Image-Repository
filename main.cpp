#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstdlib> //atoi and atof string conversion
#include "hash.h"

using namespace std;

int main() {
	Hash imageHash;
	string line;
	ifstream imageFile("image.txt");
	if (!imageFile.is_open()) {
		cout << "Unable to open file image.txt" << endl;
		return -1;
	}

	//Read the first line of domestic-stu.txt, which specifies
	//the file format. And then print it out to the screen
	getline(imageFile, line);
	cout << "File format: " << line << endl << endl;
	while (getline(imageFile, line)) {
		istringstream ss(line);
		string s_imageName, s_imageColour, s_imageType, s_imageStock, s_imagePrice, s_imageDiscount;
		int imageStock;
		double imagePrice;
		int imageDiscount;

		getline(ss, s_imageName, ',');

		getline(ss, s_imageColour, ',');

		getline(ss, s_imageType, ',');

		getline(ss, s_imageStock, ',');
		imageStock = atoi(s_imageStock.c_str());

		getline(ss, s_imagePrice, ',');
		imagePrice = atof(s_imagePrice.c_str());

		getline(ss, s_imageDiscount, ',');
		imageDiscount = atoi(s_imageDiscount.c_str());

		//Hash stream and add to repository
		imageHash.addImage(s_imageName, s_imageColour, s_imageType, imageStock, imagePrice, imageDiscount);
	}
	imageFile.close();
	string nameInput, tagInput, colourInput, typeInput, s_stockInput, s_priceInput, s_discountInput;
	int stockInput;
	double priceInput;
	int discountInput;
	vector<string> parsedInput;

	cout << "\nSearch image by name\n";
	getline(cin, nameInput);
	if (imageHash.searchImageByName(nameInput) != NULL)
		cout << imageHash.searchImageByName(nameInput);

	/*** Need to fix ***\
	cout << "\nSearch image by tag\n";
	getline(cin, tagInput);
	parsedInput = imageHash.stringParser(tagInput);
	for (int i = 0; i < imageHash.searchImageByTag(parsedInput).size(); i++) {
		cout << i << ". \n";
		cout << imageHash.searchImageByTag(parsedInput)[i];
		cout << endl << endl;
	}
	*/

	cout << "\nAdd an Image\n";
	cout << "\nInput Image Name\n";
	getline(cin, nameInput);
	
	cout << "\nInput Image Colour\n";
	getline(cin, colourInput);

	cout << "\nInput Image Type\n";
	getline(cin, typeInput);

	cout << "\nInput Image Stock\n";
	getline(cin, s_stockInput);
	stockInput = atoi(s_stockInput.c_str());

	cout << "\nInput Image Price\n";
	getline(cin, s_priceInput);
	priceInput = atof(s_priceInput.c_str());

	cout << "\nInput Image Discount\n";
	//cin.ignore();
	getline(cin, s_discountInput);
	discountInput = atoi(s_discountInput.c_str());

	imageHash.addImage(nameInput, colourInput, typeInput, stockInput, priceInput, discountInput);
	cout << endl;
	cout << imageHash.searchImageByName(nameInput);
	cout << endl << endl;


	cout << "\nDelete an Image\n";
	cout << "\nInput the name of the product you want to delete\n";
	getline(cin, nameInput);
	imageHash.deleteImage(nameInput);
	cout << "\n----Search Check----\n";
	imageHash.searchImageByName(nameInput);

	return 0;
}
