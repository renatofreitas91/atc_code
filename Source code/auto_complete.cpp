// C++ program to demonstrate auto-complete feature 
// using Trie data structure. 
//source:https://www.geeksforgeeks.org/auto-complete-feature-using-trie/
#include "stdafx.h"
using namespace std;

// Alphabet size (# of symbols) 
#define ALPHABET_SIZE (91) 

// Converts key current character into index 
// use only ' ' through 'z' and lower case 
#define CHAR_TO_INDEX(c) ((int)c - (int)' ') 

// trie node 
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];

	// isWordEnd is true if the node represents 
	// end of a word 
	bool isWordEnd;
};

// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = new TrieNode;
	pNode->isWordEnd = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

// If not present, inserts key into trie. If the 
// key is prefix of trie node, just marks leaf node 
void insert(struct TrieNode *root, const string key)
{
	struct TrieNode *pCrawl = root;

	for (int level = 0; level < abs((int)key.length()); level++)
	{
		int index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf 
	pCrawl->isWordEnd = true;
}

// Returns true if key presents in trie, else false 
bool search(struct TrieNode *root, const string key)
{
	int length = (int)key.length();
	struct TrieNode *pCrawl = root;
	for (int level = 0; level < length; level++)
	{
		int index = CHAR_TO_INDEX(key[level]);

		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->isWordEnd);
}

// Returns 0 if current node has a child 
// If all children are NULL, return 1. 
bool isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return 0;
	return 1;
}

// Recursive function to print auto-suggestions for given 
// node. 
void suggestionsRec(struct TrieNode* root, string currPrefix)
{
	// found a string in Trie with the given prefix 
	if (root->isWordEnd)
	{
		cout << currPrefix;
		cout << endl;
	}

	// All children struct node pointers are NULL 
	if (isLastNode(root))
		return;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i])
		{
			// append current character to currPrefix string 
			currPrefix.push_back(32 + i);

			// recur over the rest 
			suggestionsRec(root->children[i], currPrefix);
			// remove last character 
			currPrefix.pop_back();
		}
	}
}

// print suggestions for given query prefix. 
int printAutoSuggestions(TrieNode* root, const string query)
{
	struct TrieNode* pCrawl = root;

	// Check if prefix is present and find the 
	// the node (of last level) with last character 
	// of given string. 
	int level;
	int n = (int)query.length();
	for (level = 0; level < n; level++)
	{
		int index = CHAR_TO_INDEX(query[level]);

		// no string in the Trie has this prefix 
		if (!pCrawl->children[index])
			return 0;

		pCrawl = pCrawl->children[index];
	}

	// If prefix is present as a word. 
	bool isWord = (pCrawl->isWordEnd == true);

	// If prefix is last node of tree (has no 
	// children) 
	bool isLast = isLastNode(pCrawl);

	// If prefix is present as a word, but 
	// there is no subtree below the last 
	// matching node. 
	if (isWord && isLast)
	{
		cout << query << endl;
		return -1;
	}

	// If there are are nodes below last 
	// matching character. 
	if (!isLast)
	{
		string prefix = query;
		suggestionsRec(pCrawl, prefix);
		return 1;
	}
	return 0;
}

// Driver Code 
int autoComplete(char* query)
{
	struct TrieNode* root = getNode();
	std::string commands = "clean;exit;about;clean history;user guide;update;update x64;update portable;reset all;reset all now;reset settings;reset settings now;colors;dimensions;window;run atc;restart atc;history;predefine txt;solve txt;see abbreviations;eliminate abbreviations;enable txt detector;eliminate strings;see strings;auto solve txt;atc from cmd;atc over cmd;donate;atc facebook;atc sourceforge;current settings;mode;verbose resolution;see variables;renamed variables;eliminate variables;numerical systems;si prefixes;see results;eliminate results;solve equations system();solve quadratic equation();solve equation();triangles rectangles solver;arithmetic matrix solver;roots to polynomial();financial calculations;graph settings;graph();geometry calculations;statistics calculations;physics calculations;unit conversions;microeconomics calculations;simplify polynomial();function study();fft();ifft();atc folder;source code;to solve;scripts examples;user functions;strings;day of week();stopwatch();run stopwatch();timer();run timer();run big timer();clock();run clock();big clock();run big clock();time;calendar();actual time response;time difference calculations;shutdown;shutdown now;restart pc;restart pc now;hibernate;log off;sleep;lock;ascending order();descending order();ascii order();inverse ascii order();cos();acos();sin();asin();tan();atan();sec();asec();cosec();acosec();cotan();acotan();cosh();acosh();sinh();asinh();tanh();atanh();sech();asech();cosech();acosech();cotanh();acotanh();sinc();log();ln();logb b();rest();quotient();rtD D();sqrt();cbrt();afact();abs();+;-;*;/;^;!;e;pi;_;INF;gerror();gerrorinv();gerrorc();gerrorcinv();qfunc();qfuncinv()";
	replace(" ", "", query);
	sprintf(query, "%s", expressionF);
	std::string delimiter = ";";

	size_t pos = 0;
	std::string token;
	while ((pos = commands.find(delimiter)) != std::string::npos) {
		token = commands.substr(0, pos);
		insert(root, token);
		commands.erase(0, pos + delimiter.length());
	}

	int comp = printAutoSuggestions(root, query);

	if (comp == -1)
		cout << "No other strings found with this prefix\n";

	else if (comp == 0)
		cout << "No string found with this prefix\n";

	return 0;
}
