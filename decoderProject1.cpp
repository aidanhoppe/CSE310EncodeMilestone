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
void fillNext(char* lastColumn, char* sortedColumn, int* nextArray, int length, int* checkedArray);
void outputFromNext(int* nextArray, char* sortedColumn, int stringLength, int index);
void sortColumnInsertion(char* sortedColumn, int stringLength);
void sortColumnQuick(char* sortedColumn, int low, int high, int length);
int partition(char* sortedColumn, int low, int high, int length);


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
		while(getline(cin, toBeDecoded)){ //main loop continues while there are more lines to read
			
			stringLength = toBeDecoded.length();
			
			while(stringLength == 0){ //skip empty lines and replace them with empty lines. search for index
				cout << endl;
				getline(cin, toBeDecoded);
				stringLength = toBeDecoded.length();
			}
			
			tempColumn = new char[1000];
			
			index = atoi(toBeDecoded.c_str());  //parse the index and store as an integer
						
			getline(cin, toBeDecoded); //get the line to be decoded after you parse integer
			stringLength = toBeDecoded.length();
			
			
			int loopLength = stringLength/4+1; //create loop length by identifying how many clusters are in the string
			stringLength = 0;
			repetitions = 0;
			for(int i = 0; i<loopLength; i++){
				repetitions = toBeDecoded[4*i]-'0';
				for(int j = 0; j<repetitions; j++){
					tempColumn[stringLength + j] = toBeDecoded[2+4*i]; //add copies of char values to tempColumn representative of how many times it is repeated
				}
				stringLength += repetitions; //iterate string length by repetitions to always print on new indices
			}
			

			//dynamically declare the important structures for this algorithm based on current string length
			lastColumn = new char[stringLength];
			sortedColumn = new char[stringLength];
			checkedArray = new int[stringLength];
			nextArray = new int[stringLength];
			
			for(int i = 0; i<stringLength; i++){ //copy tempColumn to last and sorted. sorted will then be sorted
				lastColumn[i] = tempColumn[i];
				sortedColumn[i] = tempColumn[i];
			}
			delete[] tempColumn;
			
			if(sortType == "insertion"){ //sort the unsorted 'sortedColumn' using either insertion or quicksort
				sortColumnInsertion(sortedColumn, stringLength);
			} else {
				sortColumnQuick(sortedColumn, 0 , stringLength-1, stringLength);
			}
			
			fillNext(lastColumn, sortedColumn, nextArray, stringLength, checkedArray); //create the 'next' array from last column and sorted column
			
			outputFromNext(nextArray, sortedColumn, stringLength, index); //print out the final strings from nextArray and sortedColumn
			
			delete[] lastColumn; //clean up before looping again
			delete[] sortedColumn;
		}
		
		return 1;
		
}

void fillNext(char* lastColumn, char* sortedColumn, int* nextArray, int length, int* checkedArray){ //fillNext will create the integer array nextAray by utilizing checkedArray
	for(int i = 0; i<length; i++){                                                                  	//and the sorted and last columns.
		for(int j = 0; j<length; j++){
			if(sortedColumn[i] == lastColumn[j] && checkedArray[j]!=1){
				nextArray[i]=j;
				checkedArray[j] = 1;
				break;
			}
		}
	}
}

void outputFromNext(int* nextArray, char* sortedColumn, int stringLength, int index){ //create string output from nextArray and sortedColumn
	for(int i = 0; i<stringLength; i++){
		cout << sortedColumn[index];
		index = nextArray[index];
	}
	cout<<endl;
}

void sortColumnInsertion(char* sortedColumn, int stringLength){ //insertion sort for array of chars
	int i, j;
	char key;
	for(j =1; j<stringLength; j++){ //this is the insertion sort implementation
		key = sortedColumn[j];
		i = j-1;
		while(i >= 0 && sortedColumn[i]>key){  //compareString returns true if block[i] is greater than key 
			sortedColumn[i+1] = sortedColumn[i];
			i--;
		}
		sortedColumn[i+1] = key;
	}
}

void sortColumnQuick(char* sortedColumn, int low, int high, int length){ //quicksort body -- relies on partition
	if(low<high){
		int partitionIndex = partition(sortedColumn, low, high, length);
		sortColumnQuick(sortedColumn, low, partitionIndex-1, length);
		sortColumnQuick(sortedColumn, partitionIndex+1, high, length);
	}
}

int partition(char* sortedColumn, int low, int high, int length){ //most of the heavy lifting of quicksort. chooses partition element and swaps around it
	char pivot = sortedColumn[high];
	int i = (low-1);
	
	for(int j = low; j <= high-1; j++){
		if(pivot > sortedColumn[j]){
			i++;
			char temp = sortedColumn[i]; //swap around partition element if needed
			sortedColumn[i] = sortedColumn[j];
			sortedColumn[j] = temp;
		}
	}
	char temp = sortedColumn[i+1];
	sortedColumn[i+1] = sortedColumn[high];
	sortedColumn[high] = temp;
	return(i+1);
}
