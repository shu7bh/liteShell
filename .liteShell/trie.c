// C++ program to demonstrate auto-complete feature
// using Trie data structure.

#include <stdbool.h>
#include "trie.h"
#include "../headers.h"
#include "../commandAutoCompletion.h"

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = malloc(sizeof(TrieNode));
    pNode->isWordEnd = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie.  If the
// key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root,  const char* key)
{
    struct TrieNode *pCrawl = root;

    for (int level = 0; level < strlen(key); level++)
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
bool search(struct TrieNode *root, const char* key)
{
    int length = strlen(key);
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
void suggestionsRec(struct TrieNode* root, char* currPrefix, FILE* fp)
{
    // found a char* in Trie with the given prefix
    if (root->isWordEnd)
        /*fprintf(fp, "%s\n", currPrefix);*/
        printf("%s\n", currPrefix);

    // All children struct node pointers are NULL
    if (isLastNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            // append current character to currPrefix char*
            currPrefix[strlen(currPrefix) + 1] = 0;
            currPrefix[strlen(currPrefix)] = 97 + i;

            // recur over the rest
            suggestionsRec(root->children[i], currPrefix, fp);
            // remove last character
            currPrefix[strlen(currPrefix) - 1] = 0;
        }
    }
}

// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, const char* query, FILE* fp)
{
    struct TrieNode* pCrawl = root;

    // Check if prefix is present and find the
    // the node (of last level) with last character
    // of given char*.
    int level;
    int n = strlen(query);
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);

        // no char* in the Trie has this prefix
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
        /*fprintf(fp, "%s\n", query);*/
        printf("%s\n", query);
        return -1;
    }

    // If there are are nodes below last
    // matching character.
    if (!isLast)
    {
        char* prefix = strdup(query);
        suggestionsRec(pCrawl, prefix, fp);
        return 1;
    }
    return 0;
}

// Driver Code
int main()
{
    struct TrieNode* root = getNode();
    /*insert(root, "hello");*/
    /*insert(root, "dog");*/
    /*insert(root, "hell");*/
    /*insert(root, "cat");*/
    /*insert(root, "a");*/
    /*insert(root, "hel");*/
    /*insert(root, "help");*/
    /*insert(root, "helps");*/
    /*insert(root, "helping");*/
    /*int comp = printAutoSuggestions(root, "helping");*/

    FILE* rp = fopen("args.txt", "r");

    if (!rp)
    {
        perror("file error");
        return -1;
    }

    char* search = malloc(SIZE);
    fgets(search, SIZE, rp);

    char* string = malloc(SIZE);

    while (fgets(string, SIZE, rp))
    {
        char* str = strtok_r(string, "\n", &string);
        /*if (str[0] >= 'a' && str[0] <= 'z')*/
        insert(root, str);
    }

    char* str = strtok_r(search, "\n", &search);

    fclose(rp);

    FILE* wp = fopen("return.txt", "w");

    printf("\n");
    int r = printAutoSuggestions(root, str, wp);

    /*fseek(wp, 0, SEEK_SET);*/
    /*fprintf(wp, "%d", r);*/
    printf("%d", r);

    /*fclose(wp);*/
    /*if (comp == -1)*/
        /*printf("No other char*s found with this prefix\n");*/

    /*else if (comp == 0)*/
        /*printf("No char* found with this prefix\n");*/

    /*return 0;*/
}
