#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <iostream>
using namespace std;

const int ALPHABET_SIZE = 26;

// Структура узела дерева 
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
    int freq=0;
};

TrieNode* getNewNode(void);
void insert(TrieNode*, string);
bool search(TrieNode*, string);
TrieNode* wordjump(TrieNode* root, string key);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, string, int depth = 0);
void findMinPrefixes(TrieNode*, char[], int, string&);
void findWords(TrieNode*, char[], int, string&);
#endif