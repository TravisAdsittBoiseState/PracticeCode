#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

/**
 *
 * This is a simple program to demonstrate and practice the use of 
 * external precompiled libraries, as well as an implementation of 
 * the Rabin-Karp substringg search algorithm.
 *
 * Author: Travis Adsitt
 *
 * 10AUG18
 *
 */

int main(int argc,char**args){

	char* sentence = malloc(100 * sizeof(char));
	char* searchFor = malloc(10 * sizeof(char));
	int hashVal, strLen, index, found, temp, cont;


	printf("Type a string to search:\n");
	fgets(sentence,100,stdin);

	printf("Type a sub-string to search for:\n");
	fgets(searchFor,10,stdin);
	
	strLen = 0;

	while(searchFor[strLen++] != '\n'){};
	strLen--; //This discludes the \n for hashing purposes

	hashVal = hash(searchFor, strLen);

	index = 0;
	found = 0;

	//This is an implementation of the Rabin-Karp substring search
	//which runs in O(n) time.
	while(!found){
		temp = hash(&sentence[index],strLen);
		if(hash(&sentence[index],strLen) == hashVal){
			for(temp = 0; temp < strLen; temp++){
				if(sentence[index + temp] != searchFor[temp]) break;
			}
			if(temp == strLen) found = 1;
		}
		if(sentence[index + strLen] == '\n' && !found) break;
	
		index++;

	}

	free(sentence);
	free(searchFor);

	printf("The sub-string %s in the string!\n",found?"was":"wasn't");

}
