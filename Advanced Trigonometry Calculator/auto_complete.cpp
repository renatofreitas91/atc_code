// C++ program to demonstrate auto-complete feature 
// using Trie data structure. 
//source:https://www.geeksforgeeks.org/auto-complete-feature-using-trie/
#include "stdafx.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
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
	bool isWord = (pCrawl->isWordEnd == (bool)true);

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

static const char* getAutoCompleteVocabulary()
{
	return
		"create matrix();"
		"solve equation();solveequation();solve quadratic equation();solve equations system();"
		"solver();simplify polynomial();function study();roots to polynomial();"
		"graph();graph settings;"
		"arithmetic matrix solver;triangles rectangles solver;financial calculations;"
		"geometry calculations;statistics calculations;physics calculations;unit conversions;microeconomics calculations;"
		"fft();ifft();"
		"ascending order();descending order();ascii order();inverse ascii order();"
		"cos();acos();sin();asin();tan();atan();sec();asec();cosec();acosec();cotan();acotan();"
		"cosh();acosh();sinh();asinh();tanh();atanh();sech();asech();cosech();acosech();cotanh();acotanh();"
		"radcos();radacos();radsin();radasin();radtan();radatan();radsec();radasec();radcosec();radacosec();radcotan();radacotan();"
		"degcos();degacos();degsin();degasin();degtan();degatan();degsec();degasec();degcosec();degacosec();degcotan();degacotan();"
		"goncos();gonacos();gonsin();gonasin();gontan();gonatan();gonsec();gonasec();goncosec();gonacosec();goncotan();gonacotan();"
		"sinc();log();ln();logb b();rest();quotient();rtD D();sqrt();cbrt();afact();abs();det();"
		"gerror();gerrorinv();gerrorc();gerrorcinv();qfunc();qfuncinv();"
		"min();max();avg();linsnum();colsnum();getlins();getcols();"
		"strlen();countoccurrences();iscontained();iscontainedbyindex();iscontainedvariable();isequal();isvariable();istowrite();"
		"atc();calc();for();atc_;"
		"maxprec;maxprecision;higher precision;higher precision();higherprecision();"
		"dp;dppi;dpe;true;false;INF;_INF;e;pi;i;res;_;+;-;*;/;^;!;"
		"mode;numerical systems;si prefixes;verbose resolution;verbose resolution();actual time response;actual time response();"
		"current settings;colors;dimensions;window;auto adjust window;"
		"reset all;reset all now;reset settings;reset settings now;"
		"enable atc intro;disable atc intro;clean;clean history;exit;about;history;user guide;"
		"run atc;restart atc;new tab;new instance;new atc tab;new atc instance;"
		"check for updates;update;update x64;update portable;donate;atc facebook;atc sourceforge;"
		"atc folder;source code;to solve;scripts examples;user functions;strings;"
		"predefine txt;solve txt;solve txt();auto solve txt;open txt();opentxt();atc from cmd;atc over cmd;"
		"see variables;renamed variables;eliminate variables;see results;eliminate results;"
		"see abbreviations;eliminate abbreviations;enable txt detector;see strings;eliminate strings;"
		"higher precision;"
		"day of week();stopwatch();run stopwatch();timer();run timer();run big timer();clock();run clock();big clock();run big clock();"
		"time;calendar();actual time response;time difference calculations;"
		"shutdown;shutdown now;restart pc;restart pc now;hibernate;log off;sleep;lock;";
}

static std::string toLowerAscii(const std::string& value)
{
	std::string result = value;
	for (size_t i = 0; i < result.length(); i++) {
		result[i] = (char)std::tolower((unsigned char)result[i]);
	}
	return result;
}

static std::string toInlineCompletionToken(const std::string& token)
{
	if (token.length() >= 2 && token[token.length() - 2] == '(' && token[token.length() - 1] == ')') {
		return token.substr(0, token.length() - 1);
	}

	return token;
}

static void addSuggestion(std::vector<std::string>& suggestions, const std::string& token)
{
	if (token.empty()) {
		return;
	}

	std::string normalizedToken = toInlineCompletionToken(token);
	std::string lowerToken = toLowerAscii(normalizedToken);
	for (size_t i = 0; i < suggestions.size(); i++) {
		if (toLowerAscii(suggestions[i]) == lowerToken) {
			return;
		}
	}

	suggestions.push_back(normalizedToken);
}

static void appendUserFunctionSuggestions(std::vector<std::string>& suggestions)
{
	if (atcPath == nullptr || strlen(atcPath) == 0) {
		return;
	}

	char searchPath[MAX_PATH];
	snprintf(searchPath, sizeof(searchPath), "%s\\User functions\\*.txt", atcPath);

	WIN32_FIND_DATAA findData;
	HANDLE findHandle = FindFirstFileA(searchPath, &findData);
	if (findHandle == INVALID_HANDLE_VALUE) {
		return;
	}

	do {
		if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
			std::string fileName = findData.cFileName;
			if (fileName.length() > 4 && toLowerAscii(fileName.substr(fileName.length() - 4)) == ".txt") {
				std::string functionName = fileName.substr(0, fileName.length() - 4);
				if (!functionName.empty()) {
					addSuggestion(suggestions, "atc_" + functionName + "(");
				}
			}
		}
	} while (FindNextFileA(findHandle, &findData));

	FindClose(findHandle);
}

static std::vector<std::string> loadInputHistory()
{
	std::vector<std::string> history;
	if (atcPath == nullptr || strlen(atcPath) == 0) {
		return history;
	}

	char historyPath[MAX_PATH];
	snprintf(historyPath, sizeof(historyPath), "%s\\history.txt", atcPath);

	FILE* file = nullptr;
	fopen_s(&file, historyPath, "r");
	if (file == nullptr) {
		return history;
	}

	std::vector<char> buffer((size_t)DIM);
	while (fgets(buffer.data(), DIM, file) != nullptr) {
		std::string line = buffer.data();
		while (!line.empty() && (line[line.length() - 1] == '\n' || line[line.length() - 1] == '\r')) {
			line.erase(line.length() - 1);
		}

		if (line.length() > 1 && line[0] == '>') {
			std::string expression = line.substr(1);
			if (!expression.empty()) {
				if (history.empty() || history[history.size() - 1] != expression) {
					history.push_back(expression);
				}
			}
		}
	}

	fclose(file);
	return history;
}

static std::vector<std::string> getAutoCompleteSuggestions()
{
	std::vector<std::string> suggestions;
	std::string commands = getAutoCompleteVocabulary();
	const std::string delimiter = ";";
	size_t pos = 0;
	while ((pos = commands.find(delimiter)) != std::string::npos) {
		std::string token = commands.substr(0, pos);
		addSuggestion(suggestions, token);
		commands.erase(0, pos + delimiter.length());
	}

	appendUserFunctionSuggestions(suggestions);
	return suggestions;
}

static bool compareCompletionCandidate(const std::string& left, const std::string& right)
{
	if (left.length() != right.length()) {
		return left.length() < right.length();
	}

	return toLowerAscii(left) < toLowerAscii(right);
}

static size_t getCompletionPrefixStart(const std::string& line, size_t cursor)
{
	if (cursor > line.length()) {
		cursor = line.length();
	}

	size_t length = cursor;
	while (length > 0) {
		char current = line[length - 1];
		if (current == '+' || current == '-' || current == '*' || current == '/' ||
			current == '^' || current == '\\' || current == ';' || current == ',' ||
			current == '(' || current == ')' || current == '[' || current == ']' ||
			current == '{' || current == '}' || current == '!') {
			return length;
		}
		length--;
	}

	return 0;
}

static void copyEditorLineToBuffer(char* line, int capacity, const std::string& value)
{
	if (line == nullptr || capacity <= 0) {
		return;
	}

	strncpy_s(line, capacity, value.c_str(), _TRUNCATE);
}

static void redrawConsoleInputLine(const std::string& value, size_t cursor, size_t previousLength)
{
	printf("\r>%s", value.c_str());
	if (previousLength > value.length()) {
		for (size_t i = value.length(); i < previousLength; i++) {
			printf(" ");
		}
	}

	printf("\r>%s", value.c_str());
	for (size_t i = cursor; i < value.length(); i++) {
		printf("\b");
	}
}

static void resetCompletionCycle(std::string& cyclePrefix, std::vector<std::string>& cycleMatches, size_t& cycleIndex, size_t& cycleStart)
{
	cyclePrefix = "";
	cycleMatches.clear();
	cycleIndex = 0;
	cycleStart = 0;
}

static std::vector<std::string> findCompletionMatches(const std::vector<std::string>& suggestions, const std::string& prefix)
{
	std::vector<std::string> matches;
	std::string lowerPrefix = toLowerAscii(prefix);
	for (size_t i = 0; i < suggestions.size(); i++) {
		std::string lowerSuggestion = toLowerAscii(suggestions[i]);
		if (lowerSuggestion.find(lowerPrefix) == 0) {
			matches.push_back(suggestions[i]);
		}
	}

	std::sort(matches.begin(), matches.end(), compareCompletionCandidate);
	return matches;
}

static int replaceCompletionToken(std::string& line, size_t& cursor, int capacity, size_t prefixStart, const std::string& prefix, const std::string& replacement)
{
	if (toLowerAscii(replacement) == toLowerAscii(prefix)) {
		printf("\a");
		return 0;
	}

	if (line.length() - prefix.length() + replacement.length() >= (size_t)capacity) {
		printf("\a");
		return 0;
	}

	line.replace(prefixStart, prefix.length(), replacement);
	cursor = prefixStart + replacement.length();
	return 1;
}

static int appendAutoCompletion(const std::vector<std::string>& suggestions, std::string& line, size_t& cursor, int capacity, std::string& cyclePrefix, std::vector<std::string>& cycleMatches, size_t& cycleIndex, size_t& cycleStart)
{
	if (capacity <= 1) {
		return 0;
	}

	if (cursor > line.length()) {
		cursor = line.length();
	}

	size_t prefixStart = getCompletionPrefixStart(line, cursor);
	std::string prefix = line.substr(prefixStart, cursor - prefixStart);
	if (prefix.empty()) {
		resetCompletionCycle(cyclePrefix, cycleMatches, cycleIndex, cycleStart);
		printf("\a");
		return 0;
	}

	bool canCycle = !cycleMatches.empty() && prefixStart == cycleStart;
	if (canCycle) {
		for (size_t i = 0; i < cycleMatches.size(); i++) {
			if (toLowerAscii(prefix) == toLowerAscii(cycleMatches[i])) {
				cycleIndex = (i + 1) % cycleMatches.size();
				return replaceCompletionToken(line, cursor, capacity, prefixStart, prefix, cycleMatches[cycleIndex]);
			}
		}
	}

	std::vector<std::string> matches = findCompletionMatches(suggestions, prefix);
	if (matches.empty()) {
		resetCompletionCycle(cyclePrefix, cycleMatches, cycleIndex, cycleStart);
		printf("\a");
		return 0;
	}

	std::string replacement = matches[0];
	if (matches.size() > 1) {
		cycleIndex = 0;
		cyclePrefix = prefix;
		cycleMatches = matches;
		cycleStart = prefixStart;
	}
	else {
		resetCompletionCycle(cyclePrefix, cycleMatches, cycleIndex, cycleStart);
	}

	return replaceCompletionToken(line, cursor, capacity, prefixStart, prefix, replacement);
}

void readConsoleInputWithTabCompletion(char* line, int capacity)
{
	if (line == nullptr || capacity <= 0) {
		return;
	}

	line[0] = '\0';
	printf(">");
	std::string editorLine = "";
	size_t cursor = 0;
	size_t previousLength = 0;
	std::vector<std::string> history = loadInputHistory();
	std::vector<std::string> suggestions = getAutoCompleteSuggestions();
	size_t historyIndex = history.size();
	std::string draftLine = "";
	std::string completionCyclePrefix = "";
	std::vector<std::string> completionCycleMatches;
	size_t completionCycleIndex = 0;
	size_t completionCycleStart = 0;

	while (true) {
		int key = _getch();

		if (key == 0 || key == 224) {
			int specialKey = _getch();
			if (specialKey == 75) {
				resetCompletionCycle(completionCyclePrefix, completionCycleMatches, completionCycleIndex, completionCycleStart);
				if (cursor > 0) {
					cursor--;
					printf("\b");
				}
			}
			else if (specialKey == 77) {
				resetCompletionCycle(completionCyclePrefix, completionCycleMatches, completionCycleIndex, completionCycleStart);
				if (cursor < editorLine.length()) {
					printf("%c", editorLine[cursor]);
					cursor++;
				}
			}
			else if (specialKey == 72) {
				resetCompletionCycle(completionCyclePrefix, completionCycleMatches, completionCycleIndex, completionCycleStart);
				if (!history.empty() && historyIndex > 0) {
					if (historyIndex == history.size()) {
						draftLine = editorLine;
					}
					previousLength = editorLine.length();
					historyIndex--;
					editorLine = history[historyIndex];
					cursor = editorLine.length();
					copyEditorLineToBuffer(line, capacity, editorLine);
					redrawConsoleInputLine(editorLine, cursor, previousLength);
				}
				else {
					printf("\a");
				}
			}
			else if (specialKey == 80) {
				resetCompletionCycle(completionCyclePrefix, completionCycleMatches, completionCycleIndex, completionCycleStart);
				if (!history.empty() && historyIndex < history.size()) {
					previousLength = editorLine.length();
					historyIndex++;
					if (historyIndex == history.size()) {
						editorLine = draftLine;
					}
					else {
						editorLine = history[historyIndex];
					}
					cursor = editorLine.length();
					copyEditorLineToBuffer(line, capacity, editorLine);
					redrawConsoleInputLine(editorLine, cursor, previousLength);
				}
				else {
					printf("\a");
				}
			}
			else if (specialKey == 71) {
				resetCompletionCycle(completionCyclePrefix, completionCycleMatches, completionCycleIndex, completionCycleStart);
				cursor = 0;
				redrawConsoleInputLine(editorLine, cursor, previousLength);
			}
			else if (specialKey == 79) {
				resetCompletionCycle(completionCyclePrefix, completionCycleMatches, completionCycleIndex, completionCycleStart);
				cursor = editorLine.length();
				redrawConsoleInputLine(editorLine, cursor, previousLength);
			}
			else if (specialKey == 83) {
				if (cursor < editorLine.length()) {
					resetCompletionCycle(completionCyclePrefix, completionCycleMatches, completionCycleIndex, completionCycleStart);
					previousLength = editorLine.length();
					editorLine.erase(cursor, 1);
					historyIndex = history.size();
					draftLine = editorLine;
					copyEditorLineToBuffer(line, capacity, editorLine);
					redrawConsoleInputLine(editorLine, cursor, previousLength);
				}
			}
			continue;
		}

		if (key == '\r') {
			copyEditorLineToBuffer(line, capacity, editorLine);
			printf("\n");
			return;
		}

		if (key == '\b') {
			if (cursor > 0) {
				resetCompletionCycle(completionCyclePrefix, completionCycleMatches, completionCycleIndex, completionCycleStart);
				previousLength = editorLine.length();
				editorLine.erase(cursor - 1, 1);
				cursor--;
				historyIndex = history.size();
				draftLine = editorLine;
				copyEditorLineToBuffer(line, capacity, editorLine);
				redrawConsoleInputLine(editorLine, cursor, previousLength);
			}
			continue;
		}

		if (key == '\t') {
			previousLength = editorLine.length();
			if (appendAutoCompletion(suggestions, editorLine, cursor, capacity, completionCyclePrefix, completionCycleMatches, completionCycleIndex, completionCycleStart) != 0) {
				historyIndex = history.size();
				draftLine = editorLine;
				copyEditorLineToBuffer(line, capacity, editorLine);
				redrawConsoleInputLine(editorLine, cursor, previousLength);
			}
			continue;
		}

		if (key >= 32 && key <= 126) {
			if (editorLine.length() + 1 < (size_t)capacity) {
				resetCompletionCycle(completionCyclePrefix, completionCycleMatches, completionCycleIndex, completionCycleStart);
				previousLength = editorLine.length();
				editorLine.insert(cursor, 1, (char)key);
				cursor++;
				historyIndex = history.size();
				draftLine = editorLine;
				copyEditorLineToBuffer(line, capacity, editorLine);
				if (cursor == editorLine.length()) {
					printf("%c", key);
				}
				else {
					redrawConsoleInputLine(editorLine, cursor, previousLength);
				}
			}
			else {
				printf("\a");
			}
		}
	}
}

// Driver Code 
int autoComplete(char* query)
{
	struct TrieNode* root = getNode();
	std::string commands = getAutoCompleteVocabulary();
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
