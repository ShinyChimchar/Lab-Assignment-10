#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
	int counter;
	struct trie* next[26];
};


// Initializes a trie structure
struct Trie* createTrie()
{
	struct Trie* myTree = malloc(sizeof(struct Trie));
	myTree->counter = 0;
	for (int i = 0; i < 26; i++){
		myTree->next[i] = NULL;
	
	return myTree;
}

}
int i = 0;

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word)
{
	struct Trie* current = pTrie;
	for (int i = 0; word[i] != '\0'; i++) {
		int index = word[i] - 'a';
		if (!current->next[index]) {
			current->next[index] = createNode();
		}
		current = current->next[index];
	}
	current->counter++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie* pTrie, char* word)
{
	struct Trie* current = pTrie;
	for (int i = 0; word[i] != '\0'; i++) {
		int index = word[i] - 'a';
		if (!current->next[index]) {
			return 0; 
		}
		current = current->next[index];
	}
	return current->counter;
}

// deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie)
{
	for (int i = 0; i < 26; i++) {
		if (pTrie->next != NULL) {
			deallocateTrie(pTrie->next[i]);
		}
		free (pTrie);
	}
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords)
{
	FILE* file = fopen(filename, "r");

	int num_Words = 0;
	char word[100]; // Assuming max word length is 99 characters
	while (scanf(file, "%s", word) != EOF) {
		pInWords[num_Words] = strdup(word);
		num_Words++;
	}

	fclose(file);
	return num_Words;
}

int main(void)
{
	char* inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i = 0; i < numWords; ++i)
	{
		printf("%s\n", inWords[i]);
	}

	struct Trie* pTrie = createTrie();
	for (int i = 0; i < numWords; i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
	for (int i = 0; i < 5; i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}