
/*
 * A library with a single function for practicing the use
 * of external libraries in C.
 *
 * Author: Travis Adsitt
 *
 * 10AUG18
 */

/*
 * A hash function that is the character's ASCII values added up.
 */
unsigned int hash(char* string, int len){

	unsigned int hashVal = 0;
	int index = 0;

	while(index < len){

		hashVal += string[index++];
	
	}

	return hashVal;

}
