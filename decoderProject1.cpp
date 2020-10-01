/*
Author: Aidan Hoppe
Date: 9/15/20
Description: This is the encoding portion of assignment 1. It creates string permutation and then sorts them
	with insertion sort. This is then used to encode the line of text and is printed to a new file.
*/


#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

char* arrayFromLine();
char* sortArray(char* array, int size);
void fillNext(char* lastColumn, char* sortedColumn);
char* sortColumnInsertion(char* lastColumn);
char* sortColumnQuick(char* lastColumn);


int main(int argc, char** argv) {
	
		string toBeDecoded;
		int stringLength;
		int index;
		char* lastColumn;
		char* sortedColumn;
		int* checkedArray;
		int* nextArray;
		int repetitions;
		char* tempColumn;
		string sortType;
		
		
		sortType = argv[1];
		if(sortType != "quick" && sortType != "insertion"){
			cout << "Sorry, only quick and insertion sort are supported" << endl;
			return 0;
		}
		while(getline(cin, toBeDecoded)){
			
			stringLength = toBeDecoded.length();
			
			while(stringLength == 0){
				cout << endl;
				getline(cin, toBeDecoded);
				stringLength = toBeDecoded.length();
			}
			
			cout << toBeDecoded;
			
			tempColumn = new char[1000];
			
			index = atoi(toBeDecoded.c_str());
			
			getline(cin, toBeDecoded);
			stringLength = toBeDecoded.length();
			
			//char* array = arrayFromLine(toBeDecoded);
			
			int loopLength = stringLength/4+1;
			stringLength = 0;
			for(int i = 0; i<loopLength; i++){
				repetitions = toBeDecoded[4*i]-'0';
				for(int j = 0; j<repetitions; j++){
					tempColumn[stringLength + j] = toBeDecoded[2+4*i];
					//cout << toBeDecoded[2+4*i];
				}
				stringLength += repetitions;
			}
			
			lastColumn = new char[stringLength];
			sortedColumn = new char[stringLength];
			checkedArray = new int[stringLength];
			nextArray = new int[stringLength];
			
			for(int i = 0; i<stringLength; i++){
				lastColumn[i] = tempColumn[i];
				//cout << lastColumn[i];
			}
			delete tempColumn;
			
			if(sortType == "insertion"){
				sortedColumn = sortColumnInsertion(lastColumn);
			} else {
				sortedColumn = sortColumnQuick(lastColumn);
			}
			
			fillNext(lastColumn, sortedColumn);
			
			//stringLength = array.length();
			
			//char* checkedArray = new char[stringLength];
		}
		return 1;
		
}

void fillNext(char* lastColumn, char* sortedColumn){
	
}

char* sortColumnInsertion(char* lastColumn){
	
}

char* sortColumnQuick(char* lastColumn){
	
}
