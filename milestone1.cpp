/*
Author: Aidan Hoppe
Date: 9/15/20
Description: This is the encoding portion of assignment 1. It creates string permutation and then sorts them
	with insertion sort. This is then used to encode the line of text and is printed to a new file.
*/

#include <iostream>
#include <cstdlib>
using namespace std;

char* stringToArray(string str, int length);
char** arrayToBlock(char* array, int length);
int sortBlockInsertion(char** block, int length);
void sortBlockQuick(char** block, int low, int high, int length);
int partition(char** block, int low, int high, int length);
char* getLast(char** block, int length);
bool compareString(char* str1, char* str2, int length);
int arrayToString(char* array, int length);

int main(int argc, char** argv) {
	
	
	int result;
	int stringLength = -1;
	string sortType;
	string toBeEncoded;
	char* stringArray;
	char** dataBlock;

	
	sortType = argv[1]; //read the sortType from the command-line parameter
	if(sortType != "quick" && sortType != "insertion"){
		cout << "Sorry, only quick and insertion sort are supported" << endl;
		return 0;
	}
	
	while(getline(cin, toBeEncoded)){     //continue while there are still more lines to read in the file
		
		stringLength = toBeEncoded.length(); //initialize string length
		
		stringArray = stringToArray(toBeEncoded, stringLength); //convert string to array
		
		//the dataBlock is the length x length sized 2d array of permutations of the original string
		dataBlock = arrayToBlock(stringArray, stringLength);    //convert array to permutations
	
		//sortBlock uses insertion sort and a compareString method to arrange the permutation string in increasing ascii order
		if(sortType == "insertion"){
			sortBlockInsertion(dataBlock, stringLength); //sort the block
		} else {
			sortBlockQuick(dataBlock, 0, stringLength-1, stringLength);
		}
	
		for(int i = 0; i<stringLength; i++){   //find the index of the original line and store it in result
			if(dataBlock[i][stringLength]==0){
				result = i;
				break;
			}
		}
		
		stringArray = getLast(dataBlock, stringLength); //get the last column of the sorted block and store in stringArray
	
		if(stringLength == 0){  //if the string read in is a blank line, just print 1 blank line and move on
			cout << endl;
		} else {  //if the string read in isn't blank...
			cout << result<< endl; //'result' is the index that the original string occupies in the sorted block
			arrayToString(stringArray, stringLength); //this prints the array to the encoded string format e.g. 1d2a1e1f
			for(int i = 0; i<stringLength; i++){ //clear up used memory on the heap after the encoded output has been printed
				delete[] dataBlock[i];
			}
			delete[] dataBlock;
		}
	}
	
	return 0;
}

//This converts the final array of characters to a string that is printed in encoded format
int arrayToString(char* arr, int length){
	int index = 0;
	int counter = 1;
	char currentChar = arr[index]; //current and next Char are created to track 'clusters' of characters
	char nextChar = arr[index+1];
	while(index < length){ //finishes when the index becomes the length so there are no more characters to print
		if(nextChar!=currentChar){   //when the characters change, update the encoded message
			if(index != length-1){
				cout << counter << " " << currentChar << " ";
			} else {
				cout << counter << " " << currentChar;
			}
			index++;
			currentChar = nextChar;
			nextChar = arr[index+1];
			counter = 1;
		} else {  //when the characters are the same, count how many have been seen and iterate down the array
			counter++;
			index++;
			currentChar = arr[index];
			nextChar = arr[index+1];
		}
	}
	cout << endl;
	return 0;
}

//this converts the input string into an array by adding it elementwise into a new array of size length
char* stringToArray(string str, int length){
	char* temp = new char[length];
	for(int i = 0; i<length; i++){
		temp[i] = str[i];
	}
	return temp;
}

//this turns the array of characters (sudo-string) into the block of string permutations
char** arrayToBlock(char* arr, int length){
	char** block = new char*[length];
	for(int i = 0; i< length; i++){ //dynamically create arrays of characters with 1 extra space to include index tracker
		block[i] = new char[length+1];
	}
	
	for(int i = 0; i<length; i++){ //add the permutations with a looping character sequence
		for(int j=0; j<length; j++){
			block[i][j] = arr[(i+j)%length];
		}
		block[i][length] = i;
	}
	return block;
}

//this sorts the block of string permutations by the string's ascii values
int sortBlockInsertion(char** block, int length){
	int i, j;
	char* key;
	for(j =1; j<length; j++){ //this is the insertion sort implementation
		key = block[j];
		i = j-1;
		while(i >= 0 && compareString(block[i],key, length)){  //compareString returns true if block[i] is greater than key 
			block[i+1] = block[i];
			i--;
		}
		block[i+1] = key;
	}
	return 0;
}

void sortBlockQuick(char** block, int low, int high, int stringLength){ //this is the implementation of quicksort which has been adapted to work for the block
	if(low<high){
		int partitionIndex = partition(block, low, high, stringLength);
		sortBlockQuick(block, low, partitionIndex-1, stringLength);
		sortBlockQuick(block, partitionIndex+1, high, stringLength);
	}
}

int partition(char** block, int low, int high, int length){  //this is an accessory to quicksort which will choose a partition
	char* pivot = block[high];
	int i = (low-1);
	
	for(int j = low; j <= high-1; j++){
		if(compareString(pivot, block[j], length)){
			i++;
			char* temp = block[i]; //this will swap around the partition if needed
			block[i] = block[j];
			block[j] = temp;
		}
	}
	char* temp = block[i+1];
	block[i+1] = block[high];
	block[high] = temp;
	return(i+1);
}

//this collects the last column of our sorted block and stores it in an array
char* getLast(char** block, int length){
	char* lastColumn = new char[length];
	for(int i = 0; i<length; i++){
		lastColumn[i] = block[i][length-1];
	}
	return lastColumn;
}

//this acts as a string comparison for two character arrays
bool compareString(char* str1, char* str2, int length){
	for(int i =0; i<length; i++){ //the characters are compared elementwise and a t/f value is immediately returned when a difference is marked
		if(str1[i]>str2[i]){
			return true;
		} else if(str1[i]<str2[i]) {
			return false;
		}
	}
	return false;
}

