/*
Author: Aidan Hoppe
Date: 6/8/20
Description: This is assignment 3, the land generation project.
*/

#include <iostream>
#include <cstdlib>
using namespace std;

char* stringToArray(string str, int length);
char** arrayToBlock(char* array, int length);
int sortBlock(char** block, int length);
char* getLast(char** block, int length);
bool compareString(char* str1, char* str2, int length);
int arrayToString(char* array, int length);

int main(int argc, char** argv) {
	
	int stringLength = -1;
	string sortType;
	string toBeEncoded;
	char* stringArray;
	char** dataBlock;
	int result;
	string input;
	
	sortType = argv[1];
	if(sortType == "quick"){
		cout << "Sorry, quicksort is not supported yet" << endl;
		return 0;
	}
	
	while(getline(cin, toBeEncoded)){
		stringLength = toBeEncoded.length();
	
		stringArray = stringToArray(toBeEncoded, stringLength); //convert string to array
		dataBlock = arrayToBlock(stringArray, stringLength);    //convert array to permutations block
	
		sortBlock(dataBlock, stringLength); //sort the block
	
		for(int i = 0; i<stringLength; i++){   //find the index of the original line and store it in result
			if(dataBlock[i][stringLength]==0){
				result = i;
				break;
			}
		}
		
		stringArray = getLast(dataBlock, stringLength); //get the last column of the sorted block and store in stringArray
	
		if(stringLength == 0){
			cout << endl;
		} else {
			cout << result<< endl;
			arrayToString(stringArray, stringLength); //get a string 'result' that holds the result we want to print
			for(int i = 0; i<stringLength; i++){
				delete[] dataBlock[i];
			}
			delete[] dataBlock;
		}
	}
	return 0;
}

int arrayToString(char* arr, int length){
	int index = 0;
	int counter = 1;
	char currentChar = arr[index];
	char nextChar = arr[index+1];
	while(index < length){
		if(nextChar!=currentChar){
			cout << counter << currentChar;
			index++;
			currentChar = nextChar;
			nextChar = arr[index+1];
			counter = 1;
		} else {
			counter++;
			index++;
			currentChar = arr[index];
			nextChar = arr[index+1];
		}
	}
	cout << endl;
	return 0;
}

char* stringToArray(string str, int length){
	char* temp = new char[length];
	for(int i = 0; i<length; i++){
		temp[i] = str[i];
	}
	return temp;
}

char** arrayToBlock(char* arr, int length){
	char** block = new char*[length];
	for(int i = 0; i< length; i++){
		block[i] = new char[length+1];
	}
	
	for(int i = 0; i<length; i++){
		for(int j=0; j<length; j++){
			block[i][j] = arr[(i+j)%length];
		}
		block[i][length] = i;
	}
	return block;
}

int sortBlock(char** block, int length){
	int i, j;
	char* key;
	for(j =1; j<length; j++){
		key = block[j];
		i = j-1;
		while(i >= 0 && compareString(block[i],key, length)){   
			block[i+1] = block[i];
			i--;
		}
		block[i+1] = key;
	}
	return 0;
}

char* getLast(char** block, int length){
	char* lastColumn = new char[length];
	for(int i = 0; i<length; i++){
		lastColumn[i] = block[i][length-1];
	}
	return lastColumn;
}


bool compareString(char* str1, char* str2, int length){
	for(int i =0; i<length; i++){
		if(str1[i]>str2[i]){
			return true;
		} else if(str1[i]<str2[i]) {
			return false;
		}
	}
	return false;
}

