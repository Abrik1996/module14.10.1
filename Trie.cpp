
#include "Trie.h"

using namespace std;
// ��������� ����� ���� � ������� ������
TrieNode* getNewNode(void)
{
    // �������� ������ �� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;

    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � ������ ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index]) {
            node->children[index] = getNewNode();
        }
        node->freq++;
        node = node->children[index];
    }

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}

// ���������� true ���� ���� ���� � ������, ����� false 
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// ���������� true ���� root ����� ����, ����� false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

TrieNode* wordjump(TrieNode* root, string key)
{
    for (int i = 0; i < key.length(); i++)
    {
        root = root->children[static_cast<int>(key[i] - 'a')]; 
    }
    return root;
}

// ����������� ������� �������� ����� �� ������ 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // ���� ������ ������ 
    if (!root)
        return nullptr;
    root->freq--;
    // ���� ����� �� ����� ����� 
    if (depth == key.size()) {

        // ���� ���� ������ �� ����� ����� 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // ���� �� ����� �� ����� �����, ���������� �������� ��� ������� 
    // ���������������� ������� 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // ���� � ����� ��� ��������� ����� 
    // (������ ������ ���� ��� �������� �������), 
    // � �� �� ������������� ������ ������. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // ���������� ����� ������
    return root;
}


// �� ���������� ��������� �������
void findMinPrefixes(TrieNode* root, char buf[], int ind, string& res)
{
    if (!root)
        return;
    if (root->freq <= 1 )
    {
        buf[ind] = '\0';
        res += (string)buf + ' ';
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
        {
            buf[ind] = i + 'a';
            findMinPrefixes(root->children[i], buf, ind + 1, res);
        }
    }
 //   std::cout << res << " ";
}
void findWords(TrieNode* root, char buf[], int ind, string& res)
{
    if (!root)
        return;
    if (root->isEndOfWord)
    {
        buf[ind] = '\0';
        res += (string)buf + ' ';
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != nullptr)
        {
            buf[ind] = i + 'a';
            findWords(root->children[i], buf, ind + 1, res);
        }
    }
    //   std::cout << res << " ";
}