#ifndef TRIE_H
#define TRIE_H

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE 260

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) (int)c // - (int)'a')

typedef struct TrieNode TrieNode;

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isWordEnd;
};

void insert(struct TrieNode *root, const char *key);
bool search(struct TrieNode *root, const char *key);

#endif
