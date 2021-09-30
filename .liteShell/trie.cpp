// C++ program to demonstrate auto-complete feature
// using Trie data structure.
//#include<bits/stdc++.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (300)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) (int)c

// trie node
struct TrieNode;

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void);

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const string key);

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const string key);

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool isLastNode(struct TrieNode* root);

// Recursive function to print auto-suggestions for given
// node.
void suggestionsRec(struct TrieNode* root, string currPrefix, ofstream& fout, string path);

// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, const string query, ofstream& fout);

void traverse(std::string& prefix, TrieNode& node, ofstream& fout);

// Driver Code
int main(int argc, char** argv)
{
    TrieNode* root = getNode();

    char* filePath = realpath(argv[0], NULL);
    char* p = strrchr(filePath, '/');

    p[0] = 0;
    string path = filePath;
    ifstream fin(path + "/args.txt");

    if (fin.eof())
    {
        perror("ifstream error");
        return 0;
    }

    string query, word;
    getline(fin, query);

    while ((getline(fin, word)))
        insert(root, word);

    ofstream fout(path + "/return.txt");

    printAutoSuggestions(root, query, fout);

	return 0;
}

struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];

	// isWordEnd is true if the node represents
	// end of a word
	bool isWordEnd;
};

struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = new TrieNode;
	pNode->isWordEnd = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
};

int printAutoSuggestions(TrieNode* root, string query, ofstream& fout)
{
	struct TrieNode* pCrawl = root;

	// Check if prefix is present and find the
	// the node (of last level) with last character
	// of given string.
	int level;

    if (query.back() == '/')
    {
        std::string prefix = query;
        traverse(prefix, *root, fout);
        return 1;
    }

    std::size_t found = query.find_last_of("/");

    string path;
    if (found != std::string::npos)
    {
        path += query.substr(0, found) + '/';
        query = query.substr(found + 1);
    }
    else
        path = "";

	int n = query.length();

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
		fout << path + query << '\n';
		return -1;
	}

	// If there are are nodes below last
	// matching character.
	if (!isLast)
	{
		string prefix = query;
		suggestionsRec(pCrawl, prefix, fout, path);
		return 1;
	}
    return 0;
}

void suggestionsRec(struct TrieNode* root, string currPrefix, ofstream& fout, string path)
{
	// found a string in Trie with the given prefix
	if (root->isWordEnd)
		fout << path + currPrefix << '\n';

	// All children struct node pointers are NULL
	if (isLastNode(root))
		return;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i])
		{
			// append current character to currPrefix string
			currPrefix.push_back(i);

			// recur over the rest
			suggestionsRec(root->children[i], currPrefix, fout, path);
			// remove last character
			currPrefix.pop_back();
		}
	}
}

bool isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return 0;
	return 1;
}

bool search(struct TrieNode *root, const string key)
{
	int length = key.length();
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

void insert(struct TrieNode *root, const string key)
{
	struct TrieNode *pCrawl = root;

	for (int level = 0; level < key.length(); level++)
	{
		int index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isWordEnd = true;
}

void traverse(string& prefix, TrieNode& node, ofstream& fout)
{
  if (node.isWordEnd)
    fout << prefix << '\n';

  for (int index = 0; index < ALPHABET_SIZE; ++index) {
    TrieNode* pChild = node.children[index];
    if (pChild) {
      prefix.push_back(index);
      traverse(prefix, *pChild, fout);
      prefix.pop_back();
    }
  }
}
